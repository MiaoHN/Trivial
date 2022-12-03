#ifndef __CPPLOG_LOG_BACKEND_H__
#define __CPPLOG_LOG_BACKEND_H__

#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "lock_free_queue.h"
#include "log_appender.h"

namespace cpplog {

/**
 * @brief 日志后端
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
  std::mutex m_append_mutex;

  std::string m_messages;
  int m_buffersize;

  LockFreeQueue<std::string, 16> m_queue;

  bool m_running;
  bool m_all_down;

  std::vector<std::shared_ptr<LogAppender>> m_appenders;
};

}  // namespace cpplog

#endif  // __CPPLOG_LOG_BACKEND_H__