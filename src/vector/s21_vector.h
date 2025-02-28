#ifndef S21_VECTOR_H
#define S21_VECTOR_H

namespace s21 {
    template <class T>
    class vector {
        public :
            using value_type = T;
            using reference = T&;
            using const_reference = const T&;
            using iterator = T*;
            using const_iterator = const T*;
            using size_type = size_t;

            vector();
            vector(size_type n);
            vector(std::initializer_list<value_type> const &items);
            vector(const vector &v);
            vector(vector &&v) noexcept;
            ~vector();

            vector& operator=(vector &&v);
            reference at(size_type pos); 
            reference operator[](size_type pos);
            const_reference front(); 
            const_reference back() const; 
            T* data();
            iterator begin();
            iterator end();
            bool empty() const; 
            size_type size() const; 
            size_type max_size() const;
            void reserve(size_type size);
            size_type capacity() const; 
            void shrink_to_fit();
            void clear();
            iterator insert(iterator pos, const_reference value);
            void erase(iterator pos);
            void push_back(const_reference value);
            void pop_back();
            void swap(vector& other);

        private:
        size_type size_;
        size_type capacity_;
        value_type *data_;

    };
};

#include "s21_vector.hpp"

#endif