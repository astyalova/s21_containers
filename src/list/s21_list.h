#ifndef S21_LIST_H
#define S21_LIST_H

namespace s21 {
    template <class T>
    class list {
        public:
            using value_type = T;
            using reference = T&;
            using const_reference = const T&;
            class iterator = ListIterator<T>;
            class const_iterator = ListConstIterator<T>;
            using size_type = size_t;

            list();
            list(size_type n);
            list(std::initializer_list<value_type> const &items);
            list(const list &l);
            list(list &&l);
            ~list();
            reference operator=(list &&l);

            const_reference front();
            const_reference back();

            iterator begin();
            iterator end();

            bool empty();
            size_type size();
            size_type max_size();
            void clear();
            iterator insert(iterator pos, const_reference value);
            void erase(iterator pos);
            void push_back(const_reference value);
            void pop_back();
            void push_front(const_reference value);
            void pop_front();
            void swap(list& other);
            void merge(list& other);
            void splice(const_iterator pos, list& other);
            void reverse();
            void unique();
            void sort();

        private:
            struct Node {
                value_type value;
                Node *next;
                Node *prev;
                Node() : value = 0, next = nullptr, prev = nullptr {}
            }
            size_type list_;
            Node *head;
            Node *tail;
    };
};

#include "s21_list.hpp"

#endif