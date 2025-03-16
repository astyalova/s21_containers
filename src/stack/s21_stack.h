#ifndef S21_STACK_H
#define S21_STACK_H

namespace s21 {

template <class T> class stack {
public:
  // Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // Functions
  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s);
  ~stack();
  stack &operator=(stack &&s);

  // Element access
  const_reference top();
  bool empty();
  size_type size();

  // Capacity
  void push(const_reference value);
  void pop();
  void swap(stack &other);

  // Modifiers
  template <class... Args> void insert_many_back(Args &&...args);

private:
  s21::list<value_type> stack_;
};

} // namespace s21

#include "s21_stack.hpp"

#endif