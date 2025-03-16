#ifndef S21_SET_HPP
#define S21_SET_HPP

#include "s21_set.h"

namespace s21 {

template <typename Key> set<Key>::set() : BSTree<Key, Key>() {}

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const &items)
    : BSTree<Key, Key>() {
  for (auto i = items.begin(); i != items.end(); ++i) {
    BSTree<Key, Key>::insert(*i, Key());
  }
}

template <typename Key> set<Key>::set(const set &s) : BSTree<Key, Key>(s) {}

template <typename Key>
set<Key>::set(set &&s) noexcept : BSTree<Key, Key>(std::move(s)) {}

template <typename Key> set<Key>::~set() = default;

template <typename Key> set<Key> &set<Key>::operator=(set &&s) noexcept {
  BSTree<Key, Key>::operator=(std::move(s));
  return *this;
}

template <typename Key> bool set<Key>::contains(const Key &key) {
  return BSTree<Key, Key>::contains(key);
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key &key) {
  return BSTree<Key, Key>::find(key);
}

template <typename Key>
std::pair<typename set<Key>::iterator, bool>
set<Key>::insert(const value_type &value) {
  return BSTree<Key, Key>::insert(value, Key());
}

template <typename Key> bool set<Key>::empty() {
  return BSTree<Key, Key>::empty();
}

template <typename Key> typename set<Key>::iterator set<Key>::begin() const {
  return BSTree<Key, Key>::begin();
}

template <typename Key> typename set<Key>::iterator set<Key>::end() const {
  return BSTree<Key, Key>::end();
}

template <typename Key> typename set<Key>::size_type set<Key>::size() {
  return BSTree<Key, Key>::size();
}

template <typename Key> typename set<Key>::size_type set<Key>::max_size() {
  return std::numeric_limits<typename set<Key>::size_type>::max() /
         sizeof(typename set<Key>::value_type);
}

template <typename Key> void set<Key>::clear() { BSTree<Key, Key>::clear(); }

template <typename Key> void set<Key>::erase(iterator pos) {
  BSTree<Key, Key>::erase(pos);
}

template <typename Key> void set<Key>::swap(set &other) {
  BSTree<Key, Key>::swap(other);
}

template <typename Key> void set<Key>::merge(set &other) {
  BSTree<Key, Key>::merge(other);
}

template <typename Key>
template <class... Args>
s21::vector<std::pair<typename set<Key>::iterator, bool>>
set<Key>::insert_many(Args &&...args) {
  s21::vector<std::pair<iterator, bool>> results;
  results.reserve(sizeof...(args));

  for (const auto &arg : {args...}) {
    results.push_back(insert(arg));
  }
  return results;
}
} // namespace s21
#endif