#include "log.h"

#include <utility>

LogBackend g_log_backend;

void StdoutAppender::output(const std::string& msg) {
  std::cout << msg << std::endl;
}

FileAppender::FileAppender(const std::string& name, int reopen_duration)
    : m_reopen_duration(reopen_duration) {
  filename = name;
  // TODO print something to inform true format of file-log names
  time_t t = time(nullptr);
  char buf[64];
  strftime(buf, sizeof(buf), "%Y_%m_%d_%H_%M_%S", localtime(&t));
  filename += "." + std::string(buf, strlen(buf));
  filename += ".log";
  m_last_open = std::chrono::steady_clock::now();

  f.open(filename, std::ios::app);
}

FileAppender::~FileAppender() { f.close(); }

void FileAppender::output(const std::string& msg) {
  std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
  std::chrono::steady_clock::duration duration = now - m_last_open;
  if (static_cast<int>((double)duration.count() / 1e6) >= m_reopen_duration) {
    reopen();
    m_last_open = now;
  }

  f << msg << std::endl;
}

void FileAppender::reopen() {
  f.close();
  f.open(filename, std::ios::app);
}

LogBackend::LogBackend() : m_running(true), m_all_down(false) {
  m_worker = new std::thread([this] { return LogBackend::output(this); });
  // m_appenders.push_back(std::make_shared<StdoutAppender>());
  m_appenders.push_back(std::make_shared<FileAppender>("test"));
}

LogBackend::~LogBackend() {
  m_running = false;
  while (!m_queue.empty()) {
  }
  while (!m_all_down) {
  }
  m_worker->join();
  delete m_worker;
}

void LogBackend::append(const std::string& msg) {
  while (!m_queue.enqueue(msg)) {
  }
}

void LogBackend::output(void* ptr) {
  auto* backend = (LogBackend*)ptr;
  std::string msg;
  while (backend->m_running || !backend->m_queue.empty()) {
    while (!backend->m_queue.empty()) {
      if (backend->m_queue.dequeue(msg)) {
        for (auto& appender : backend->m_appenders) {
          appender->output(msg);
        }
      }
    }
  }
  backend->m_all_down = true;
}

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

static thread_local Logger s_logger;

static Logger& GetLogger() { return s_logger; }

LogEventWrapper::~LogEventWrapper() { GetLogger().log(m_event); }

std::shared_ptr<LogEvent> LogEventWrapper::getEvent() const { return m_event; }

std::stringstream& LogEventWrapper::getSs() { return m_event->getSs(); }

void Logger::log(const std::shared_ptr<LogEvent>& event) {
  std::lock_guard<std::mutex> locker(m_mutex);
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
