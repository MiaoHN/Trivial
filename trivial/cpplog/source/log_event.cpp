#include "log_event.h"

#include "logger.h"

namespace cpplog {

LogEvent::LogEvent(const char* filename, LogLevel level, uint64_t time,
                   int line, pid_t pid)
    : m_filename(filename),
      m_time(time),
      m_line(line),
      m_level(level),
      m_pid(pid) {}

std::stringstream& LogEvent::getSs() { return m_ss; }

LogLevel LogEvent::getLevel() const { return m_level; }

pid_t LogEvent::getPid() const { return m_pid; }

LogEventWrapper::LogEventWrapper(std::shared_ptr<LogEvent> event)
    : m_event(std::move(event)) {}

LogEventWrapper::~LogEventWrapper() { Logger::GetLogger().log(m_event); }

std::shared_ptr<LogEvent> LogEventWrapper::getEvent() const { return m_event; }

std::stringstream& LogEventWrapper::getSs() { return m_event->getSs(); }

}  // namespace cpplog
