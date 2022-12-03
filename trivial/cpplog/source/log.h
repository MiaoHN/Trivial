#ifndef __LOG_H__
#define __LOG_H__

#include <cstring>
#if WIN32
#include <windows.h>
#else
#include <sys/syscall.h>
#endif
#include <unistd.h>

#include <chrono>
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

#include "lock_free_queue.h"
#include "log_event.h"

#if WIN32
#define LOG_LEVEL(level)                                                     \
  cpplog::LogEventWrapper(                                                   \
      std::make_shared<cpplog::LogEvent>(__FILE__, level, time(0), __LINE__, \
                                         GetCurrentThreadId()))              \
      .getSs()
#else
#define LOG_LEVEL(level)                                                     \
  cpplog::LogEventWrapper(                                                   \
      std::make_shared<cpplog::LogEvent>(__FILE__, level, time(0), __LINE__, \
                                         syscall(SYS_gettid)))               \
      .getSs()
#endif

#define LOG_TRACE() LOG_LEVEL(cpplog::LogLevel::Trace)
#define LOG_INFO() LOG_LEVEL(cpplog::LogLevel::Info)
#define LOG_DEBUG() LOG_LEVEL(cpplog::LogLevel::Debug)
#define LOG_WARN() LOG_LEVEL(cpplog::LogLevel::Warn)
#define LOG_ERROR() LOG_LEVEL(cpplog::LogLevel::Error)
#define LOG_FATAL() LOG_LEVEL(cpplog::LogLevel::Fatal)

#endif  // __LOG_H__