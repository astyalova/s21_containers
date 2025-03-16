#ifndef S21_SET_H
#define S21_SET_H

namespace s21 {
template <typename Key> class set : public BSTree<Key, Key> {
public:
  // Member type
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename BSTree<Key, Key>::iterator;
  using const_iterator = typename BSTree<Key, Key>::const_iterator;
  using size_type = size_t;

  // Member functions
  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s) noexcept;
  ~set();
  set &operator=(set &&s) noexcept;

  // Iterators
  iterator begin() const;
  iterator end() const;

  // Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Modifiers
  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);
  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  // Lookup
  bool contains(const Key &key);
  iterator find(const Key &key);
};
} // namespace s21

#include "s21_set.hpp"

#endif
