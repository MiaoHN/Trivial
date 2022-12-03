#include "logger.h"

#include <cstring>

#include "log_backend.h"

namespace cpplog {

static LogBackend g_log_backend;

void Logger::log(const std::shared_ptr<LogEvent>& event) {
  g_log_backend.append(formatEvent(event));
}

static std::string ToString(LogLevel level) {
  switch (level) {
    case LogLevel::Trace:
      return "[trace] ";
    case LogLevel::Info:
      return "[info]  ";
    case LogLevel::Debug:
      return "[debug] ";
    case LogLevel::Warn:
      return "[warn]  ";
    case LogLevel::Error:
      return "[error] ";
    case LogLevel::Fatal:
      return "[fatal] ";
    default:
      return "[unknown] ";
  }
}

std::string Logger::formatEvent(const std::shared_ptr<LogEvent>& event) {
  std::string msg = event->getSs().str();
  time_t t = time(nullptr);
  char buf[64];
  strftime(buf, sizeof(buf), "%H:%M:%S", localtime(&t));
  std::string pid_str = "[" + std::to_string(event->getPid()) + "] ";
  std::string time_str = "[" + std::string(buf, strlen(buf)) + "] ";
  return time_str + pid_str + ToString(event->getLevel()) + msg;
}

Logger& Logger::GetLogger() {
  static Logger s_logger;
  return s_logger;
}

}  // namespace cpplog
