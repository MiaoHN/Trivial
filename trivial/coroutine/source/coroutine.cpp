#include "coroutine.h"

#include <cstring>

#include "scheduler.h"

thread_local int tCoroutineCount = 0;

Coroutine::Coroutine() : _id(tCoroutineCount++) {}

Coroutine::Coroutine(std::function<void()> callback)
    : _callback(callback),
      _size(0),
      _capacity(0),
      _id(tCoroutineCount++),
      _scheduler(Scheduler::Get()),
      _status(Status::Ready),
      _stack(nullptr) {
  Scheduler::Get()->addCoroutine(this);
}

Coroutine::~Coroutine() {}

void Coroutine::resume() { Scheduler::Get()->resume(_id); }

void Coroutine::yield() { Scheduler::Get()->yield(); }

void Coroutine::SaveStack(Coroutine* coroutine, char* top) {
  char dummy = 0;
  if (coroutine->_capacity < top - &dummy) {
    delete coroutine->_stack;
    coroutine->_capacity = top - &dummy;
    coroutine->_stack    = new char[coroutine->_capacity];
  }
  coroutine->_size = top - &dummy;
  memcpy(coroutine->_stack, &dummy, coroutine->_size);
}
