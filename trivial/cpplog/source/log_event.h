#ifndef __CPPLOG_LOG_EVENT_H__
#define __CPPLOG_LOG_EVENT_H__

#include <pthread.h>

#include <cstdint>
#include <memory>
#include <sstream>

namespace cpplog {

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

  std::shared_ptr<LogEvent> getEvent() const;

  std::stringstream& getSs();

 private:
  std::shared_ptr<LogEvent> m_event;
};

}  // namespace cpplog

#endif  // __CPPLOG_LOG_EVENT_H__