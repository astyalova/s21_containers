#ifndef S21_MAP_HPP
#define S21_MAP_HPP
#include "s21_map.h"
namespace s21 {

template <typename Key, typename T> map<Key, T>::map() : BSTree<Key, T>() {}

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const &items)
    : BSTree<Key, T>(items) {}

template <typename Key, typename T>
map<Key, T>::map(const map &m) : BSTree<Key, T>(m) {}

template <typename Key, typename T>
map<Key, T>::map(map &&m) noexcept : BSTree<Key, T>(std::move(m)) {}

template <typename Key, typename T> map<Key, T>::~map() = default;

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(map &&m) noexcept {
  BSTree<Key, T>::operator=(std::move(m));
  return *this;
}

template <typename Key, typename T> T &map<Key, T>::operator[](const Key &key) {
  return BSTree<Key, T>::operator[](key);
}

template <typename Key, typename T> T &map<Key, T>::at(const Key &key) {
  return BSTree<Key, T>::at(key);
}

template <typename Key, typename T> bool map<Key, T>::contains(const Key &key) {
  return BSTree<Key, T>::contains(key);
}

template <typename Key, typename T> bool map<Key, T>::empty() {
  return BSTree<Key, T>::empty();
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::size() {
  return BSTree<Key, T>::size();
}

template <typename Key, typename T> void map<Key, T>::clear() {
  BSTree<Key, T>::clear();
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool>
map<Key, T>::insert(const Key &key, const T &obj) {
  return BSTree<Key, T>::insert(key, obj);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool>
map<Key, T>::insert(const value_type &value) {
  return BSTree<Key, T>::insert(value.first, value.second);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool>
map<Key, T>::insert_or_assign(const Key &key, const T &obj) {
  return BSTree<Key, T>::insert_or_assign(key, obj);
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() const {
  return BSTree<Key, T>::begin();
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() const {
  return BSTree<Key, T>::end();
}

template <typename Key, typename T> void map<Key, T>::erase(iterator pos) {
  BSTree<Key, T>::erase(pos);
}

template <typename Key, typename T> void map<Key, T>::swap(map &other) {
  BSTree<Key, T>::swap(other);
}

template <typename Key, typename T> void map<Key, T>::merge(map &other) {
  BSTree<Key, T>::merge(other);
}

template <typename Key, typename T>
template <class... Args>
std::vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args &&...args) {
  std::vector<std::pair<typename map<Key, T>::iterator, bool>> vec;
  for (const auto &arg : {args...}) {
    vec.push_back(insert(arg));
  }
  return vec;
}

} // namespace s21
#endif