#include "log.h"

LogBackend g_log_backend;

void StdoutAppender::output(const std::string& msg) {
  std::cout << msg << std::endl;
}

FileAppender::FileAppender(const std::string& name) : m_reopen_duration(1000) {
  filename = name;
  // TODO print something to inform true format of file-log names
  struct tm tm;
  time_t t = time(0);
  localtime_r(&t, &tm);
  char buf[64];
  strftime(buf, sizeof(buf), "%Y-%m-%d-%H:%M:%S", &tm);
  filename += "." + std::string(buf, strlen(buf));
  filename += ".log";
  m_last_open = std::chrono::high_resolution_clock::now();

  f.open(filename, std::ios::app);
}

FileAppender::~FileAppender() { f.close(); }

void FileAppender::output(const std::string& msg) {
  std::chrono::time_point<std::chrono::high_resolution_clock> now =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = now - m_last_open;
  if (duration.count() >= m_reopen_duration) {
    reopen();
    m_last_open = now;
  }

  f << msg << std::endl;
}

void FileAppender::reopen() {
  f.close();
  f.open(filename, std::ios::app);
}

LogQueue::LogQueue(int max_size) : m_max_size(max_size), m_cursor(0) {
  m_queue.resize(m_max_size);
}

void LogQueue::append(const std::string& msg) {
  std::lock_guard<std::mutex> locker(m_mutex);
  if (m_cursor == m_max_size) {
    std::cout << "LogQueue::append(): queue overflow!!!" << std::endl;
    return;
  }
  m_queue[m_cursor++] = msg;
}

void LogQueue::clear() {
  std::lock_guard<std::mutex> locker(m_mutex);
  m_cursor = 0;
}

int LogQueue::size() {
  std::lock_guard<std::mutex> locker(m_mutex);
  return m_cursor;
}

bool LogQueue::empty() {
  std::lock_guard<std::mutex> locker(m_mutex);
  return m_cursor == 0;
}

bool LogQueue::full() {
  std::lock_guard<std::mutex> locker(m_mutex);
  return m_cursor == m_max_size;
}

LogBackend::LogBackend() : m_running(true) {
  m_worker = new std::thread(std::bind(&LogBackend::output, this));
  m_appenders.push_back(std::make_shared<StdoutAppender>());
  m_appenders.push_back(std::make_shared<FileAppender>("test"));
  m_input_queue = new LogQueue();
  m_output_queue = new LogQueue();
}

LogBackend::~LogBackend() {
  m_running = false;
  if (!m_input_queue->empty()) {
    std::vector<std::string>& logs = m_input_queue->m_queue;
    int size = m_input_queue->size();
    for (int i = 0; i < size; ++i) {
      for (auto& appender : m_appenders) {
        appender->output(logs[i]);
      }
    }
  }
  delete m_input_queue;
  delete m_output_queue;
  m_worker->join();
  delete m_worker;
}

void LogBackend::append(const std::string& msg) {
  std::lock_guard<std::mutex> locker1(m_input_mutex);
  if (m_input_queue->full()) {
    while (!m_output_queue->empty()) {
    }

    std::lock_guard<std::mutex> locker2(m_output_mutex);
    LogQueue* temp_ptr = m_input_queue;
    m_input_queue = m_output_queue;
    m_output_queue = temp_ptr;
  }
  m_input_queue->append(msg);
}

void LogBackend::output(void* ptr) {
  LogBackend* backend = (LogBackend*)ptr;
  std::mutex& mutex = backend->m_output_mutex;
  while (backend->m_running) {
    if (backend->m_output_queue == nullptr) continue;
    if (!backend->m_output_queue->empty()) {
      std::lock_guard<std::mutex> locker(mutex);
      std::vector<std::string>& logs = backend->m_output_queue->m_queue;
      int size = backend->m_output_queue->size();
      for (int i = 0; i < size; ++i) {
        for (auto& appender : backend->m_appenders) {
          appender->output(logs[i]);
        }
      }
      backend->m_output_queue->clear();
    }
  }
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
    : m_event(event) {}

static thread_local Logger s_logger;

static Logger& GetLogger() { return s_logger; }

LogEventWrapper::~LogEventWrapper() { GetLogger().log(m_event); }

std::shared_ptr<LogEvent> LogEventWrapper::getEvent() const { return m_event; }

std::stringstream& LogEventWrapper::getSs() { return m_event->getSs(); }

void Logger::log(std::shared_ptr<LogEvent> event) {
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

std::string Logger::formatEvent(std::shared_ptr<LogEvent> event) {
  std::string msg = event->getSs().str();
  struct tm tm;
  time_t t = time(0);
  localtime_r(&t, &tm);
  char buf[64];
  strftime(buf, sizeof(buf), "%H:%M:%S", &tm);
  std::string pid_str = "[" + std::to_string(event->getPid()) + "] ";
  std::string time_str = "[" + std::string(buf, strlen(buf)) + "] ";
  return time_str + pid_str + ToString(event->getLevel()) + msg;
}
