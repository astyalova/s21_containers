#ifndef S21_MAP_H
#define S21_MAP_H

namespace s21 {

template <typename Key, typename T> class map : public BSTree<Key, T> {
public:
  // Member type
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename BSTree<Key, T>::iterator;
  using const_iterator = typename BSTree<Key, T>::const_iterator;
  using size_type = size_t;

  // Member functions
  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m) noexcept;
  ~map();
  map &operator=(map &&m) noexcept;

  // Map Element access
  T &at(const Key &key);
  T &operator[](const Key &key);

  // Map Iterators
  iterator begin() const;
  iterator end() const;

  // Map Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Map Modifiers
  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const Key &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);
  void erase(iterator pos);
  void swap(map &other);
  void merge(map &other);
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  // Map Lookup
  bool contains(const Key &key);
};
} // namespace s21

#include "s21_map.hpp"

#include "../BSTree/s21_tree.h"

#endif
