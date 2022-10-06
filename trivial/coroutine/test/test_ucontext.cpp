#include <stdlib.h>
#include <ucontext.h>

#include <iostream>

static ucontext_t uctx_main, uctx_func1, uctx_func2;

void func1() {
  std::cout << "func1: started" << std::endl;
  std::cout << "func1: swapcontext(&uctx_func1, &uctx_func2)" << std::endl;
  swapcontext(&uctx_func1, &uctx_func2);
  std::cout << "func1: returning" << std::endl;
  swapcontext(&uctx_func1, &uctx_main);
}

void func2() {
  std::cout << "func2: started" << std::endl;
  std::cout << "func2: swapcontext(&uctx_func2, &uctx_func1)" << std::endl;
  swapcontext(&uctx_func2, &uctx_func1);
  std::cout << "func2: returning" << std::endl;
  swapcontext(&uctx_func2, &uctx_main);
}

int main(int argc, char *argv[]) {
  char func1_stack[16384];
  char func2_stack[16384];

  getcontext(&uctx_func1);
  uctx_func1.uc_stack.ss_sp   = func1_stack;
  uctx_func1.uc_stack.ss_size = sizeof(func1_stack);
  uctx_func1.uc_link          = nullptr;
  makecontext(&uctx_func1, func1, 0);

  getcontext(&uctx_func2);
  uctx_func2.uc_stack.ss_sp   = func2_stack;
  uctx_func2.uc_stack.ss_size = sizeof(func2_stack);
  uctx_func2.uc_link          = nullptr;
  makecontext(&uctx_func2, func2, 0);

  std::cout << "main: swapcontext(&uctx_main, &uctx_func2)" << std::endl;
  swapcontext(&uctx_main, &uctx_func2);

  std::cout << "main: exiting" << std::endl;
  return 0;
}