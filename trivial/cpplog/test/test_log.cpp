#include <algorithm>
#include <thread>
#include <vector>

#include "log.h"
#include "timer.h"

void test_log() {
  Timer timer;
  int lines = 1000000;
  for (int i = 0; i < lines; ++i) {
    LOG_INFO() << "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  }
}

int main(int argc, char const *argv[]) {
  test_log();
  return 0;
}
