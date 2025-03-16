#ifndef S21_LIST_H
#define S21_LIST_H

namespace s21 {

template <typename T> class list {
public:
  // Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  class ListIterator;
  using iterator = ListIterator;
  class ListConstIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

  // Functions
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  ~list();
  list &operator=(list &&l);

  // Element access
  const_reference front();
  const_reference back();

  // Iterators
  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  // Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(iterator pos, list &other);
  void reverse();
  void unique();
  void sort();
  template <class... Args> iterator insert_many(iterator pos, Args &&...args);
  template <class... Args> void insert_many_back(Args &&...args);
  template <class... Args> void insert_many_front(Args &&...args);

private:
  struct Node {
    value_type data;
    Node *next;
    Node *prev;
    Node(const_reference value) : data(value), next(nullptr), prev(nullptr) {}

    friend bool operator<(const typename list<T>::Node &lhs,
                          const typename list<T>::Node &rhs) {
      return lhs.data < rhs.data;
    }

    friend bool operator==(const typename list<T>::Node &lhs,
                           const typename list<T>::Node &rhs) {
      return lhs.data == rhs.data;
    }
  };

  Node *head_;
  Node *tail_;
  size_type node_size_;
};

template <typename T> class list<T>::ListIterator {
public:
  using value_type = T;
  using reference = T &;
  using pointer = T *;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;

  ListIterator(typename list<T>::Node *node) : node_(node) {}

  ListIterator operator++(int) {
    ListIterator temp = *this;
    ++(*this);
    return temp;
  }

  ListIterator operator++() {
    node_ = node_->next;
    return *this;
  }

  reference operator*() { return node_->data; }

  bool operator==(const ListIterator &other) const {
    return other.node_ == node_;
  }

  bool operator!=(const ListIterator &other) const {
    return !(*this == other.node_);
  }

  typename list<T>::Node *getNode() { return node_; }

private:
  typename list<T>::Node *node_;
};

template <typename T> class list<T>::ListConstIterator {
public:
  using value_type = T;
  using reference = const T &;
  using pointer = const T *;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;

  ListConstIterator(const typename list<T>::Node *node) : node_(node) {}

  ListConstIterator operator++(int) {
    ListIterator temp = *this;
    ++(*this);
    return temp;
  }

  ListConstIterator operator++() {
    node_ = node_->next;
    return *this;
  }

  reference operator*() const { return node_->data; }
  bool operator==(const ListConstIterator &other) const {
    return node_ == other.node_;
  }

  bool operator!=(const ListConstIterator &other) const {
    return !(*this == other.node_);
  }

  typename list<T>::Node *getNode() { return node_; }

private:
  const typename list<T>::Node *node_;
};
}; // namespace s21

#include "s21_list.hpp"

#endif