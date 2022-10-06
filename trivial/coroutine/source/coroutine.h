#ifndef __COROUTINE_H__
#define __COROUTINE_H__

#include <ucontext.h>

#include <functional>
#include <memory>

class Scheduler;

class Coroutine {
  friend class Scheduler;

 public:
  enum class Status {
    Dead,
    Ready,
    Running,
    Suspend,
  };

  Coroutine();
  Coroutine(std::function<void()> callback);
  ~Coroutine();

  void resume();

  void yield();

  Status getStatus() { return _status; }
  void   setStatus(Status status) { _status = status; }

  static void SaveStack(Coroutine* coroutine, char* top);

 private:
  ucontext_t _context;

  int _id;

  Status _status;

  char* _stack;
  int   _size;
  int   _capacity;

  Scheduler* _scheduler;

  std::function<void()> _callback;
};

#endif  // __COROUTINE_H__