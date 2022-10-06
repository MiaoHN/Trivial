#include <iostream>

#include "coroutine.h"
#include "scheduler.h"

void func1() { std::cout << "-----" << std::endl; }

void func2() { std::cout << "+++++" << std::endl; }

int main(int argc, char const *argv[]) {
  Coroutine coroutine1(func1);
  Coroutine coroutine2(func2);

  coroutine2.resume();
  coroutine1.resume();

  return 0;
}
