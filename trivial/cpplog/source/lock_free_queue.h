#ifndef __LOCK_FREE_QUEUE_H__
#define __LOCK_FREE_QUEUE_H__

#include <atomic>
#include <vector>

template <typename T, int N = 1024>
class LockFreeQueue {
 public:
  struct Element {
    std::atomic<bool> full;
    T data;
  };
  LockFreeQueue() : m_data(N), m_read_index(0), m_write_index(0) {}

  bool empty() { return m_read_index == m_write_index; }

  bool enqueue(T value) {
    int write_index = 0;
    Element* e = nullptr;
    do {
      write_index = m_write_index.load(std::memory_order_relaxed);
      if (write_index >=
          m_read_index.load(std::memory_order_relaxed) + m_data.size()) {
        return false;
      }
      int index = write_index % m_data.size();
      e = &m_data[index];
      if (e->full.load(std::memory_order_relaxed)) {
        return false;
      }
    } while (!m_write_index.compare_exchange_strong(
        write_index, write_index + 1, std::memory_order_release,
        std::memory_order_relaxed));
    e->data = std::move(value);
    e->full.store(true, std::memory_order_release);
    return true;
  }

  bool dequeue(T& value) {
    int read_index = 0;
    Element* e = nullptr;
    do {
      read_index = m_read_index.load(std::memory_order_relaxed);
      if (read_index >= m_write_index.load(std::memory_order_relaxed)) {
        return false;
      }
      size_t index = read_index % m_data.size();
      e = &m_data[index];
      if (!e->full.load(std::memory_order_relaxed)) {
        return false;
      }
    } while (!m_read_index.compare_exchange_strong(read_index, read_index + 1,
                                                   std::memory_order_release,
                                                   std::memory_order_relaxed));
    value = std::move(e->data);
    e->full.store(false, std::memory_order_release);
    return true;
  }

 private:
  std::vector<Element> m_data;
  std::atomic<int> m_read_index;
  std::atomic<int> m_write_index;
};

#endif  // __LOCK_FREE_QUEUE_H__