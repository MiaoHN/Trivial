#ifndef __LOG_H__
#define __LOG_H__

#include <string.h>
#include <sys/syscall.h>
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
   * @param name file name will be `name-<time>.log`
   */
  FileAppender(const std::string& name);
  ~FileAppender();

  void output(const std::string& msg) override;

 private:
  void reopen();

 private:
  std::ofstream f;
  std::string filename;
  int m_reopen_duration;  // ms
  std::chrono::time_point<std::chrono::high_resolution_clock> m_last_open;
};

/**
 * @brief Sync log queue with mutex, default log size is 1024
 *
 */
class LogQueue {
  friend class LogBackend;

 public:
  LogQueue(int max_size = 1024);

  void append(const std::string& msg);

  void clear();

  int size();

  bool empty();

  bool full();

 private:
  std::mutex m_mutex;
  int m_max_size;
  int m_cursor;

  std::vector<std::string> m_queue;
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

  LogQueue* m_input_queue;
  LogQueue* m_output_queue;

  std::mutex m_input_mutex;
  std::mutex m_output_mutex;
  bool m_running;

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
  LogEventWrapper(std::shared_ptr<LogEvent> event);

  ~LogEventWrapper();

  std::shared_ptr<LogEvent> getEvent() const;

  std::stringstream& getSs();

 private:
  std::shared_ptr<LogEvent> m_event;
};

class Logger {
 public:
  void log(std::shared_ptr<LogEvent> event);

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
  std::string formatEvent(std::shared_ptr<LogEvent> event);

  std::mutex m_mutex;
};

#define LOG_LEVEL(level)                                                     \
  LogEventWrapper(std::make_shared<LogEvent>(__FILE__, level, time(0),       \
                                             __LINE__, syscall(SYS_gettid))) \
      .getSs()

#define LOG_TRACE() LOG_LEVEL(LogLevel::Trace)
#define LOG_INFO() LOG_LEVEL(LogLevel::Info)
#define LOG_DEBUG() LOG_LEVEL(LogLevel::Debug)
#define LOG_WARN() LOG_LEVEL(LogLevel::Warn)
#define LOG_ERROR() LOG_LEVEL(LogLevel::error)
#define LOG_FATAL() LOG_LEVEL(LogLevel::fatal)

#endif  // __LOG_H__