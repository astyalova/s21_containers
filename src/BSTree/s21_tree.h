#ifndef S21_TREE_H
#define S21_TREE_H

#include <initializer_list>
#include <cstddef>
#include <iostream>

namespace s21 {
template <class T, class K>
class BSTree {
public:
    using key_type = K;
    using map_type = T;
    using value_type = std::pair<const key_type, map_type>;
    using size_type = size_t;
    class Iterator;
    using iterator = Iterator;
    using const_iterator = const Iterator;

    struct Node {
        key_type key;
        map_type value;
        int height;
        Node* left;
        Node* right;
        Node* parent;

        Node(const key_type& k, const map_type& v) : key(k), value(v), height(1), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    class Iterator {
        public:
        Node* ptr_;
        Iterator();
        explicit Iterator(Node* ptr);
        Iterator &operator++();
        Iterator operator++(int);
        Iterator operator--(int);
        Iterator &operator--();
        bool operator==(Iterator other) const;
        bool operator!=(Iterator other) const;
        Node *operator->() const;
    };

    BSTree();
    BSTree(std::initializer_list<value_type> const &items);
    BSTree(const BSTree &other); //
    BSTree(BSTree &&other) noexcept; // 
    virtual ~BSTree(); //

    BSTree &operator=(BSTree &&other) noexcept;//

    iterator begin() const;
    iterator end() const;

    size_type size();
    size_type max_size();
    bool empty();
    void clear(Node* node);
    void clear();

protected:
    std::pair<iterator, bool> insert(const value_type &value);
    std::pair<iterator, bool> insert(const key_type &key, const map_type &obj);
    std::pair<iterator, bool> insert_or_assign(const key_type &key, const map_type &obj);
    iterator insert(const key_type &key);
    void erase(iterator pos);
    void swap(BSTree &other);
    void merge(BSTree &other);
    bool contains(const key_type &key);
    size_type count(const key_type &key);
    iterator find(const key_type &key);
    std::pair<iterator, iterator> equal_range(const key_type &key);
    iterator lower_bound(const key_type &key);
    iterator upper_bound(const key_type &key);

    map_type &at(const key_type &key);
    map_type &operator[](const key_type &key);

private:

    Node* root_;
    size_type size_;

    int getHeight(Node* node);
    int getBalanceFactor(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* node);
};
}; // namespace s21

#include "s21_tree.hpp"

#endif
