#ifndef S21_TREE_H
#define S21_TREE_H

#include <initializer_list>
#include <cstddef>
#include <iostream>

namespace s21 {
    template <class T>
    class BSTree {
        public:

        struct enum {
            Red;
            Black;
        } Сolor;

        struct Node {
            Color color;
            T value;
            Node* parent;
            Node* left;
            Node* right;
        };
    };
};

#endif