#ifndef S21_QUEUE_H
#define S21_QUEUE_H

namespace s21 {

template <class T>
class queue {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using size_type = size_t;

        queue();
        queue(std::initializer_list<value_type> const &items);
        queue(const queue &s);
        queue(queue &&s);
        ~queue();
        queue& operator=(queue &&s);

        const_reference front();
        const_reference back();

        bool empty();
        size_type size();

        void push(const_reference value);
        void pop();
        void swap(queue& other);

    private:
    s21::list<value_type> queue_;
};

} // namespace s21

#include "s21_queue.hpp"

#endif