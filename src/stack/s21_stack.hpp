#ifndef S21_STACK_HPP
#define S21_STACK_HPP

#include "s21_stack.h"

namespace s21 {

template <class T>
stack<T>::stack() : head_(nullptr), node_size_(0) {}

template <class T>
stack<T>::stack(std::initializer_list<value_type> const &items) : head_(nullptr), node_size_(0) {
    for(const auto& item : items) {
        push(item);
    }
}

template <class T>
stack<T>::stack(const stack &s) = default;

template <class T>
stack<T>::stack(stack &&s) = default;

template <class T>
stack<T>::~stack() = default;

template <class T>
stack<T>& stack<T>::operator=(stack &&s) {
    if (this != &s) {
        data_ = std::move(s.data_);
    }
    return *this;
}

template <class T>
typename stack<T>::const_reference stack<T>::top()  {
    return data_.back();
}

template <class T>
bool stack<T>::empty() const {
    return data_.empty();
}

template <class T>
typename stack<T>::size_type stack<T>::size() const { 
    return data_.size();
}

template <class T>
void stack<T>::push(const_reference value) {
    data_.push_back(value);
}

template <class T>
void stack<T>::pop() {
    data_.pop_back();
}

template <class T>
void stack<T>::swap(stack& other) {
    data_.swap(other.data_);
}

}; // namespace s21

#endif