#include "log_appender.h"

#include <cstring>
#include <iostream>

namespace cpplog {

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

}  // namespace cpplog
