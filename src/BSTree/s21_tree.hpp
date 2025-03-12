#ifndef S21_TREE_HPP
#define S21_TREE_HPP

#include "s21_tree.h"

namespace s21 {
    template <typename T, typename K>
    BSTree<T, K>::BSTree() : root_(nullptr), size_(0) {}

    template <typename T, typename K>
    BSTree<T, K>::BSTree(std::initializer_list<value_type> const &items) : root_(nullptr), size_(0) {
        for(const auto& item : items) {
            insert(item.first, item.second);
        }
    }

    // template <typename K, typename T>
    // BSTree<K, T>::BSTree(const BSTree &other) : root_(nullptr), size_(0) {
    //     if (this != &other) assign(other);
    // }


    // template <typename K, typename T>
    // BSTree<K, T>::BSTree(BSTree &&other) noexcept : size_(0) {
    //     assign(other);
    //     other.clear();
    // }

    template <typename K, typename T>
    BSTree<K, T>::~BSTree() {
        clear(root_);
        root_ = nullptr;
        size_ = 0;
    }

    template <typename K, typename T>
    BSTree<K, T> &BSTree<K, T>::operator=(BSTree &&other) noexcept {
        if (this != &other) {
            clear(root_);
            root_ = other.root_;
            size_ = other.size_;
            other.root_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }


    template <typename K, typename T>
    BSTree<K, T>::Iterator::Iterator() : ptr_(nullptr) {}

    template <typename K, typename T>
    BSTree<K, T>::Iterator::Iterator(Node* ptr) : ptr_(ptr) {}

    template <typename K, typename T>
    typename BSTree<K, T>::Iterator &BSTree<K, T>::Iterator::operator++() {
        if (!ptr_) return *this;

        if (ptr_->right) { 
            ptr_ = ptr_->right;
            while (ptr_->left) ptr_ = ptr_->left;
        } else {
            Node* parent = ptr_->parent;
            while (parent && ptr_ == parent->right) {
                ptr_ = parent;
                parent = parent->parent;
            }
            ptr_ = parent;
        }
        return *this;
    }

    template <typename K, typename T>
    typename BSTree<K, T>::Iterator BSTree<K, T>::Iterator::operator++(int) {
    Iterator temp(ptr_);
    ++(*this);
    return temp;
    }

    template <typename K, typename T>
    typename BSTree<K, T>::Iterator &BSTree<K, T>::Iterator::operator--() {
        if (!ptr_) return *this;

        if (ptr_->left) { 
            ptr_ = ptr_->left;
            while (ptr_->right) ptr_ = ptr_->right;
        } else {
            Node* parent = ptr_->parent;
            while (parent && ptr_ == parent->left) {
                ptr_ = parent;
                parent = parent->parent;
            }
            ptr_ = parent;
        }
        return *this;
    }

    template <typename K, typename T>
    typename BSTree<K, T>::Iterator BSTree<K, T>::Iterator::operator--(
        int) {
    Iterator temp(*this);
    --(*this);
    return temp;
    }

    template <typename K, typename T>
    bool BSTree<K, T>::Iterator::operator==(Iterator other) const {
    return other.ptr_ == this->ptr_;
    }

    template <typename K, typename T>
    bool BSTree<K, T>::Iterator::operator!=(Iterator other) const {
    return other.ptr_ != this->ptr_;
    }

    template <typename K, typename T>
    typename BSTree<K, T>::Node *BSTree<K, T>::Iterator::operator->()const {
    return ptr_;
    }

    template <typename T, typename K>
    typename BSTree<T, K>::iterator BSTree<T, K>::begin() const {
        Node* node = root_;
        while(node && node->left) node = node->left;
        return iterator(node);
    }

    template <typename T, typename K>
    typename BSTree<T, K>::iterator BSTree<T, K>::end() const {
        return iterator(nullptr);
    }

    template <typename T, typename K>
    bool BSTree<T, K>::empty() {
        return size_ == 0;
    }

    template <typename T, typename K>
    typename BSTree<T, K>::size_type BSTree<T, K>::size() {
        return size_;
    }

template <typename K, typename T>
typename BSTree<K, T>::size_type BSTree<K, T>::max_size() {
    return std::numeric_limits<typename BSTree<K, T>::size_type>::max() / sizeof(typename BSTree<K, T>::value_type);
}


    template <typename T, typename K>
    void BSTree<T, K>::clear() {
        clear(root_);  
        root_ = nullptr;  
    }

    template <typename T, typename K>
    void BSTree<T, K>::clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
};

#endif