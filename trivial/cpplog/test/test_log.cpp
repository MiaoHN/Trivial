#include <algorithm>
#include <thread>
#include <vector>

#include "log.h"
#include "timer.h"

static int total = 1000000;

void test_log_single_thread() {
  std::cout << "========== Single Thread ==========" << std::endl;
  Timer timer;
  int lines = total;
  for (int i = 0; i < lines; ++i) {
    LOG_INFO() << "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  }
}

void test_log_multi_thread() {
  std::cout << "========== Multi Thread ==========" << std::endl;
  Timer timer;
  int lines = total;
  std::thread t1([lines]() {
    for (int i = 0; i < lines / 10; ++i) {
      LOG_INFO() << "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    }
  });
  std::thread t2([lines]() {
    for (int i = 0; i < lines / 10; ++i) {
      LOG_INFO() << "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    }
  });
  std::thread t3([lines]() {
    for (int i = 0; i < lines / 10; ++i) {
      LOG_INFO() << "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    }
  });
  std::thread t4([lines]() {
    for (int i = 0; i < lines / 10; ++i) {
      LOG_INFO() << "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    }
  });
  std::thread t5([lines]() {
    for (int i = 0; i < lines / 10; ++i) {
      LOG_INFO() << "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    }
  });
  std::thread t6([lines]() {
    for (int i = 0; i < lines / 10; ++i) {
      LOG_INFO() << "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    }
  });
  std::thread t7([lines]() {
    for (int i = 0; i < lines / 10; ++i) {
      LOG_INFO() << "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    }
  });
  std::thread t8([lines]() {
    for (int i = 0; i < lines / 10; ++i) {
      LOG_INFO() << "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    }
  });
  std::thread t9([lines]() {
    for (int i = 0; i < lines / 10; ++i) {
      LOG_INFO() << "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    }
  });
  std::thread t10([lines]() {
    for (int i = 0; i < lines / 10; ++i) {
      LOG_INFO() << "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    }
  });
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t7.join();
  t8.join();
  t9.join();
  t10.join();
}

int main(int argc, char const *argv[]) {
  total = 1000;
  std::cout << "total log lines: " << total << std::endl;
  test_log_single_thread();
  test_log_multi_thread();
  return 0;
}
