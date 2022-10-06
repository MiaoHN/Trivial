#include "scheduler.h"

#include <cstring>

static Scheduler scheduler;

Scheduler::Scheduler() {}

Scheduler::~Scheduler() {}

void Scheduler::MainFunc(uint32_t low32, uint32_t hi32) {
  uintptr_t ptr = (uintptr_t)low32 | ((uintptr_t)hi32 << 32);

  auto scheduler = (Scheduler*)ptr;

  int id = scheduler->getRunningId();

  auto coroutine = scheduler->_coroutines[id];
  coroutine->_callback();
  scheduler->_coroutines[id]     = nullptr;
  scheduler->_runningCoroutineId = -1;
}

void Scheduler::resume(int id) {
  auto& coroutine = _coroutines[id];

  Coroutine::Status status = coroutine->getStatus();
  switch (status) {
    case Coroutine::Status::Ready: {
      getcontext(&coroutine->_context);
      coroutine->_context.uc_stack.ss_sp   = _stack;
      coroutine->_context.uc_stack.ss_size = STACK_SIZE;  // magic number
      coroutine->_context.uc_link          = &_mainContext;
      _runningCoroutineId                  = id;
      coroutine->setStatus(Coroutine::Status::Running);
      uintptr_t ptr = (uintptr_t)this;
      makecontext(&coroutine->_context, (void (*)(void))Scheduler::MainFunc, 2,
                  (uint32_t)ptr, (uint32_t)(ptr >> 32));
      swapcontext(&_mainContext, &coroutine->_context);
      break;
    }
    case Coroutine::Status::Suspend: {
      memcpy(_stack + STACK_SIZE - coroutine->_size, coroutine->_stack,
             coroutine->_size);
      _runningCoroutineId = id;
      coroutine->setStatus(Coroutine::Status::Running);
      swapcontext(&_mainContext, &coroutine->_context);
      break;
      default: {
        exit(-1);
      }
    }
  }
}

void Scheduler::yield() {
  int   id        = _runningCoroutineId;
  auto& coroutine = _coroutines[id];

  Coroutine::SaveStack(coroutine, _stack + STACK_SIZE);

  coroutine->setStatus(Coroutine::Status::Suspend);
  _runningCoroutineId = -1;
  swapcontext(&coroutine->_context, &_mainContext);
}

Scheduler* Scheduler::Get() { return &scheduler; }
