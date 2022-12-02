#include <algorithm>
#include <thread>
#include <vector>

#include "log.h"
#include "timer.h"

void one_thread_log(int lines) {
  for (int i = 0; i < lines; ++i)
    LOG_INFO()
        << "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
}

void test_one_thread(int test_times = 10, int total_lines = 1000000) {
  std::vector<double> durations;
  for (int j = 0; j < test_times; ++j) {
    Timer timer(Timer::MS, false);
    one_thread_log(total_lines);
    durations.push_back(timer.elapse());
  }
  double total = 0.0;
  for (auto item : durations) total += item;
  std::cout << "Test times: " << test_times
            << ", average time: " << total / test_times << "ms" << std::endl;
}

void test(int test_times = 10, int thread_counts = 5,
          int total_lines = 1000000) {
  std::vector<std::thread *> threads;
  for (int i = 0; i < thread_counts; ++i) {
    threads.push_back(
        new std::thread([&] { test_one_thread(test_times, total_lines); }));
  }

  for (auto &thread : threads) {
    thread->join();
    delete thread;
  }
}

int main(int argc, char const *argv[]) {
  Timer timer(Timer::MS, false);
  test(10, 1, 1000000);
  std::cout << "Total test time cost: " << timer.elapse(Timer::MS) << std::endl;
  return 0;
}
