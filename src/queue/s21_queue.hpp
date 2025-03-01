#ifndef S21_QUEUE_HPP
#define S21_QUEUE_HPP

#include "s21_queue.h"

namespace s21 {

template <class T>
queue<T>::queue() = default;

template <class T>
queue<T>::queue(std::initializer_list<value_type> const &items) {
    for (const auto& item : items) {
        this->push(item);
    }
}

template <class T>
queue<T>::queue(const queue &s) = default;

template <class T>
queue<T>::queue(queue &&s) = default;

template <class T>
queue<T>::~queue() = default;

template <class T>
queue<T>& queue<T>::operator=(queue &&s) = default;

template <class T>
typename queue<T>::const_reference queue<T>::front()  {
    return queue_.front();
}

template <class T>
typename queue<T>::const_reference queue<T>::back()  {
    return queue_.back();
}

template <class T>
bool queue<T>::empty() {
    return queue_.empty();
}

template <class T>
typename queue<T>::size_type queue<T>::size() { 
    return queue_.size();
}

template <class T>
void queue<T>::push(const_reference value) {
    queue_.push_back(value);
}

template <class T>
void queue<T>::pop() {
    queue_.pop_front();
}

template <class T>
void queue<T>::swap(queue& other) {
    queue_.swap(other.queue_);
}

}; // namespace s21

#endif