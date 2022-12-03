#ifndef __CPPLOG_LOGGER_H__
#define __CPPLOG_LOGGER_H__

#include <memory>
#include <mutex>
#include <string>

#include "log_event.h"

namespace cpplog {

/**
 * @brief 日志前端
 * @details 通过使用 log() 函数向 buffer 中添加日志，一旦 buffer 被填满，就将
 * buffer 送到日志后端的无锁队列中
 * @attention 该类通过thread_local 保证每个线程只有一个实例，无需添加锁
 *
 */
class Logger {
 public:
  /**
   * @brief 输出日志事件
   *
   * @param event
   */
  void log(const std::shared_ptr<LogEvent>& event);

  static Logger& GetLogger();

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
};

}  // namespace cpplog

#endif  // __CPPLOG_LOGGER_H__