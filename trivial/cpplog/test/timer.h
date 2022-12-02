#ifndef __TIMER_H__
#define __TIMER_H__

#include <chrono>
#include <iostream>

class Timer {
 public:
  enum Type {
    S,
    MS,
    US,
    NS,
  };
  explicit Timer(Type type = MS, bool output = true)
      : m_type(type),
        m_start(std::chrono::steady_clock::now()),
        m_output(output) {}

  double elapse(Type type = MS) {
    auto end = std::chrono::steady_clock::now();
    std::chrono::steady_clock::duration duration = end - m_start;
    switch (m_type) {
      case S:
        return static_cast<double>(duration.count()) / 1e9;
      case MS:
        return static_cast<double>(duration.count()) / 1e6;
      case US:
        return static_cast<double>(duration.count()) / 1e3;
      case NS:
      default:
        return static_cast<double>(duration.count());
    }
  }

  ~Timer() {
    if (!m_output) return;
    auto end = std::chrono::steady_clock::now();
    std::chrono::steady_clock::duration duration = end - m_start;
    switch (m_type) {
      case S:
        std::cout << duration.count() / 1e9 << "s" << std::endl;
        break;
      case MS:
        std::cout << duration.count() / 1e6 << "ms" << std::endl;
        break;
      case US:
        std::cout << duration.count() / 1e3 << "us" << std::endl;
        break;
      case NS:
        std::cout << duration.count() << "ns" << std::endl;
        break;
    }
  }

 private:
  std::chrono::steady_clock::time_point m_start;
  Type m_type;
  bool m_output;
};

#endif  // __TIMER_H__