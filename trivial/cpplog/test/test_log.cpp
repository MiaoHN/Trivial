#include <thread>

#include "log.h"

int times = 100;

void Foo() {
  for (int i = 0; i < times; ++i) LOG_INFO() << "This is Foo():" << i;
}

void Bar() {
  for (int i = 0; i < times; ++i) LOG_INFO() << "This is Bar():" << i;
}

void test_thread() {
  std::thread t1(Foo);
  std::thread t2(Bar);

  t1.join();
  t2.join();
}

void test() { Foo(); }

int main(int argc, char const *argv[]) {
  test_thread();
  return 0;
}
