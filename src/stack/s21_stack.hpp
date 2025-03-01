#ifndef S21_STACK_HPP
#define S21_STACK_HPP

#include "s21_stack.h"

namespace s21 {

template <class T>
stack<T>::stack() = default;

template <class T>
stack<T>::stack(std::initializer_list<value_type> const &items) {
    for (const auto& item : items) {
        this->push(item);
    }
}

template <class T>
stack<T>::stack(const stack &s) = default;

template <class T>
stack<T>::stack(stack &&s) = default;

template <class T>
stack<T>::~stack() = default;

template <class T>
stack<T>& stack<T>::operator=(stack &&s) = default;


template <class T>
typename stack<T>::const_reference stack<T>::top()  {
    return stack_.back();
}

template <class T>
bool stack<T>::empty() {
    return stack_.empty();
}

template <class T>
typename stack<T>::size_type stack<T>::size() { 
    return stack_.size();
}

template <class T>
void stack<T>::push(const_reference value) {
    stack_.push_back(value);
}

template <class T>
void stack<T>::pop() {
    stack_.pop_back();
}

template <class T>
void stack<T>::swap(stack& other) {
    stack_.swap(other.stack_);
}

}; // namespace s21

#endif