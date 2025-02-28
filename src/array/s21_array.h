#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <cstddef>

namespace s21 {
template <class T, size_t N>
class array {
    public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = T *;
    using const_iterator = const T *;
    using size_type = size_t;

    //Array Member functions
    array();
    array(std::initializer_list<value_type> const &items);
    array(const array &a);
    array(array &&a);
    ~array();
    array<T, N> operator=(array &&a);

    //Array Element access
    reference at(size_type pos);
    reference operator[](size_type pos);
    const_reference front();
    const_reference back();
    iterator data();

    //array iterators
    iterator begin();
    iterator end();

    //array capacity
    bool empty();
    size_type size();
    size_type max_size();

    //Array Modifiers
    void swap(array& other);
    void fill(const_reference value);

    private:
    size_type size_ = N;
    value_type array_[N];
};

};//namespace s21

#include "s21_array.hpp"

#endif
