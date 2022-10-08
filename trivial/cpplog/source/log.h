#ifndef __LOG_H__
#define __LOG_H__

namespace log {

class Logger {
 public:
  enum LogLevel {
    Trace,
    Debug,
    Info,
    Warn,
    Error,
    Fatal,
    Counts,
  };

  class SourceFile {
   public:
    template <int N>
    SourceFile(const char (&arr)[N]) : _data(arr), _size(N - 1) {
      const char* slash = strrchr(_data, '/');
      if (slash) {
        _data = slash + 1;
        _size -= static_cast<int>(_data - arr);
      }
    }

    SourceFile(const char* filename) : _data(filename) {
      const char* slash = strrchr(_data, '/');
      if (slash) {
        _data = slash + 1;
      }
      _size -= static_cast<int>(strlen(_data));
    }

    const char* _data;
    int         _size;
  };

  Logger(SourceFile file, int line);
  Logger(SourceFile file, int line, LogLevel level);
  Logger(SourceFile file, int line, LogLevel level, const char* func);
  Logger(SourceFile file, int line, bool toAbort);
  ~Logger();

  LogStream& stream() { return _impl._stream; }

  static LogLevel LogLevel();
  static void     SetLogLevel(LogLevel level);

  typedef void (*OutputFunc)(const char* msg, int len);
  typedef void (*FlushFunc)();

  static void SetOutput(OutputFunc);
  static void SetFlush(FlushFunc);

 private:
  class Impl {
   public:
    using LogLevel = Logger::LogLevel;
    Impl(LogLevel level, int oldErrno, const SourceFile& file, int line);

    void formatTime();
    void finish();

    Timestamp  _time;
    LogStream  _stream;
    LogLevel   _level;
    int        _line;
    SourceFile _basename;
  };

  Impl _impl;
};

}  // namespace log

#endif  // __LOG_H__