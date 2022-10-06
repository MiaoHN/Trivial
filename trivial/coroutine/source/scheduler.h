#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <memory>
#include <vector>

#include "coroutine.h"

class Scheduler {
 public:
  Scheduler();

  ~Scheduler();

  void resume(int id);

  void yield();

  static Scheduler* Get();

  int getRunningId() { return _runningCoroutineId; }

  void addCoroutine(Coroutine* coroutine) { _coroutines.push_back(coroutine); }

 private:
  static constexpr int STACK_SIZE = 1024 * 1024;

  ucontext_t _mainContext;
  int        _activeCoroutine;
  int        _capacity;
  char       _stack[STACK_SIZE];

  int _runningCoroutineId;

  std::vector<Coroutine*> _coroutines;

  static void MainFunc(uint32_t low32, uint32_t hi32);
};

#endif  // __SCHEDULER_H__