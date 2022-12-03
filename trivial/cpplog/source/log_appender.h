#ifndef __CPPLOG_LOG_APPENDER_H__
#define __CPPLOG_LOG_APPENDER_H__

#include <chrono>
#include <fstream>
#include <string>

namespace cpplog {

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

}  // namespace cpplog

#endif  // __CPPLOG_LOG_APPENDER_H__