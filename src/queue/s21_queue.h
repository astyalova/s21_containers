#ifndef S21_QUEUE_H
#define S21_QUEUE_H

namespace s21 {

template <class T> class queue {
public:
  // Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // Functions
  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &s);
  queue(queue &&s);
  ~queue();
  queue &operator=(queue &&s);

  // Element access
  const_reference front();
  const_reference back();

  // Capacity
  bool empty();
  size_type size();

  // Modifiers
  void push(const_reference value);
  void pop();
  void swap(queue &other);
  template <class... Args> void insert_many_back(Args &&...args);

private:
  s21::list<value_type> queue_;
};

} // namespace s21

#include "s21_queue.hpp"

#endif