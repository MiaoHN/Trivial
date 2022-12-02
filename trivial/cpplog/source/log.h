#ifndef __LOG_H__
#define __LOG_H__

#include <cstring>
#if WIN32
#include <windows.h>
#else
#include <sys/syscall.h>
#endif
#include <unistd.h>

#include <chrono>
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

#include "lock_free_queue.h"

class LogAppender {
 public:
  virtual void output(const std::string& msg) = 0;
};

class StdoutAppender : public LogAppender {
 public:
  void output(const std::string& msg) override;
};

class FileAppender : public LogAppender {
 public:
  /**
   * @brief Output log to file
   *
   * @param name file name will be `name.<time>.log`
   * @param reopen_duration ms (default 2000ms)
   */
  explicit FileAppender(const std::string& name, int reopen_duration = 2000);
  ~FileAppender();

  void output(const std::string& msg) override;

 private:
  void reopen();

 private:
  std::ofstream f;
  std::string filename;
  int m_reopen_duration;  // ms
  std::chrono::steady_clock::time_point m_last_open;
};

/**
 * @brief Log backend, output logs to appenders
 *
 */
class LogBackend {
 public:
  LogBackend();

  ~LogBackend();

  void append(const std::string& msg);

 private:
  /**
   * @brief Output log message to specified place
   *
   */
  static void output(void* ptr);

  std::thread* m_worker;

  LockFreeQueue<std::string, 1024> m_queue;

  bool m_running;
  bool m_all_down;

  std::vector<std::shared_ptr<LogAppender>> m_appenders;
};

enum class LogLevel {
  Trace,
  Info,
  Debug,
  Warn,
  Error,
  Fatal,
};

class LogEvent {
 public:
  LogEvent(const char* filename, LogLevel level, uint64_t time, int line,
           pid_t pid);

  std::stringstream& getSs();

  LogLevel getLevel() const;

  pid_t getPid() const;

 private:
  const char* m_filename;
  uint64_t m_time;
  int m_line;
  LogLevel m_level;
  pid_t m_pid;
  std::stringstream m_ss;
};

/**
 * @brief Wrap log event to append logs to backent automatically
 *
 */
class LogEventWrapper {
 public:
  explicit LogEventWrapper(std::shared_ptr<LogEvent> event);

  ~LogEventWrapper();

  [[nodiscard]] std::shared_ptr<LogEvent> getEvent() const;

  std::stringstream& getSs();

 private:
  std::shared_ptr<LogEvent> m_event;
};

class Logger {
 public:
  void log(const std::shared_ptr<LogEvent>& event);

 private:
  /**
   * @brief Format log output string
   * @details default format is:
   *
   *    [time] [pid] [level] message
   *
   * @todo enable custom log format
   * @param event
   * @return std::string
   */
  static std::string formatEvent(const std::shared_ptr<LogEvent>& event);

  std::mutex m_mutex;
};

#if WIN32
#define LOG_LEVEL(level)                                                      \
  LogEventWrapper(std::make_shared<LogEvent>(__FILE__, level, time(0),        \
                                             __LINE__, GetCurrentThreadId())) \
      .getSs()
#else
#define LOG_LEVEL(level)                                                     \
  LogEventWrapper(std::make_shared<LogEvent>(__FILE__, level, time(0),       \
                                             __LINE__, syscall(SYS_gettid))) \
      .getSs()
#endif

#define LOG_TRACE() LOG_LEVEL(LogLevel::Trace)
#define LOG_INFO() LOG_LEVEL(LogLevel::Info)
#define LOG_DEBUG() LOG_LEVEL(LogLevel::Debug)
#define LOG_WARN() LOG_LEVEL(LogLevel::Warn)
#define LOG_ERROR() LOG_LEVEL(LogLevel::Error)
#define LOG_FATAL() LOG_LEVEL(LogLevel::Fatal)

#endif  // __LOG_H__