#include "log_backend.h"

namespace cpplog {

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

}  // namespace cpplog
