#ifndef S21_MULTISET_HPP
#define S21_MULTISET_HPP

#include "s21_multiset.h"

namespace s21 {

template <typename Key> multiset<Key>::multiset() : BSTree<Key, Key>() {}

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const &items)
    : BSTree<Key, Key>() {
  for (auto i = items.begin(); i != items.end(); ++i) {
    multiset<Key>::insert(*i);
  }
}

template <typename Key>
multiset<Key>::multiset(const multiset &ms) : BSTree<Key, Key>() {
  for (auto it = ms.begin(); it != ms.end(); ++it) {
    this->insert(*it);
  }
}

template <typename Key>
multiset<Key>::multiset(multiset &&ms) noexcept
    : BSTree<Key, Key>(std::move(ms)) {}

template <typename Key> multiset<Key>::~multiset() {}

template <typename Key>
multiset<Key> multiset<Key>::operator=(multiset &&ms) noexcept {
  BSTree<Key, Key>::operator=(std::move(ms));
  return *this;
}

template <typename Key> bool multiset<Key>::contains(const Key &key) {
  return BSTree<Key, Key>::contains(key);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::find(const Key &key) {
  return BSTree<Key, Key>::find(key);
}

template <typename Key>
typename multiset<Key>::iterator
multiset<Key>::insert(const value_type &value) {
  return BSTree<Key, Key>::insert(value);
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key &key) {
  return BSTree<Key, Key>::count(key);
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key &key) {
  return BSTree<Key, Key>::equal_range(key);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key &key) {
  return BSTree<Key, Key>::lower_bound(key);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key &key) {
  return BSTree<Key, Key>::upper_bound(key);
}

template <typename Key> bool multiset<Key>::empty() {
  return BSTree<Key, Key>::empty();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::begin() const {
  return BSTree<Key, Key>::begin();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::end() const {
  return BSTree<Key, Key>::end();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::Size() {
  return BSTree<Key, Key>::Size();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::max_size() {
  return std::numeric_limits<typename multiset<Key>::size_type>::max() /
         sizeof(typename multiset<Key>::value_type);
}

template <typename Key> void multiset<Key>::clear() {
  BSTree<Key, Key>::clear();
}

template <typename Key> void multiset<Key>::erase(iterator pos) {
  BSTree<Key, Key>::erase(pos);
}

template <typename Key> void multiset<Key>::swap(multiset &other) {
  BSTree<Key, Key>::swap(other);
}

template <typename Key> void multiset<Key>::merge(multiset &other) {
  if (this != &other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      this->insert(*it);
    }
    other.clear();
  }
}

template <typename Key>
template <typename... Args>
s21::vector<std::pair<typename multiset<Key>::iterator, bool>>
multiset<Key>::insert_many(Args &&...args) {
  s21::vector<std::pair<iterator, bool>> result_vector;
  (result_vector.push_back(
       std::make_pair(insert(std::forward<Args>(args)), true)),
   ...);
  return result_vector;
}
}; // namespace s21

#endif