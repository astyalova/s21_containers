#ifndef S21_ARRAY_HPP
#define S21_ARRAY_HPP

#include "s21_array.h"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <initializer_list>

namespace s21 {
    template <class T, size_t N>
    array<T, N>::array() : size_(N), array_{} {}

    template <class T, size_t N>
    array<T, N>::array(std::initializer_list<value_type> const &items) : size_(items.size()) {
        std::copy(items.begin(), items.end(), array_);
    }

    template <class T, size_t N>
    array<T, N>::array(const array &a) : size_(a.size_) {
        std::copy(a.array_, a.array_ + N, array_);
    }

    template <class T, size_t N>
    array<T, N>::array(array &&a) : size_(a.size_) {
        std::move(a.array_, a.array_ + N, array_);
        std::fill(a.array_, a.array_ + N, T{}); //обнуление массива чтобы избежать уб
        a.size_ = 0;
    }

    //array_ автоматически уничтожается при выходе из области видимости.
    template <class T, size_t N>
    array<T, N>::~array() {}

    template <class T, size_t N>
    array<T, N> array<T, N>::operator=(array &&a) {
        if (this != &a) {
            std::swap(array_, a.array_);
            std::swap(size_, a.size_);
        }
        return *this;
    }

    template <class T, size_t N>
    typename array<T, N>::reference array<T, N>::at(size_type pos) {
        if(pos >= size()) {
            throw std::out_of_range("Index out of range");
        }
        return array_[pos];
    }

    template <class T, size_t N>
    typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
        return array_[pos];
    }

    template <class T, size_t N>
    typename array<T, N>::const_reference array<T, N>::front() {
        if(empty()) {
            throw std::out_of_range("Array is empty");
        }
        return array_[0];
    }

    template <class T, size_t N>
    typename array<T, N>::const_reference array<T, N>::back() {
        if(empty()) {
            throw std::out_of_range("Array is empty");
        }
        return array_[size_ - 1];
    }

    template <class T, size_t N>
    typename array<T, N>::iterator array<T, N>::data() {
        return array_;
    }

    template <class T, size_t N>
    typename array<T, N>::iterator array<T, N>::begin() {
        return array_;
    }

    template <class T, size_t N>
    typename array<T, N>::iterator array<T, N>::end() {
        return array_ + size_;
    }

    template <class T, size_t N>
    bool array<T, N>::empty() {
        return size_ == 0;
    }

    template <class T, size_t N>
    typename array<T, N>::size_type array<T, N>::size() {
        return size_;
    }

    template <class T, size_t N>
    typename array<T, N>::size_type array<T, N>::max_size() {
        return N;
    }

    template <class T, size_t N>
    void array<T, N>::swap(array& other) {
        for(int i = 0; i < size_; ++i) {
            std::swap(array_[i], other.array_[i]);
        }
    }

    template <class T, size_t N>
    void array<T, N>::fill(const_reference value) {
        for(int i = 0; i < size_; ++i) {
            array_[i] = value;
        }
    }

}; //namespace s21

#endif