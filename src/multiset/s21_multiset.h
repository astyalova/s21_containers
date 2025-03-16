#ifndef S21_MULTISET_H
#define S21_MULTISET_H

namespace s21 {

template <class Key> class multiset : public BSTree<Key, Key> {
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
  multiset();
  multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &ms);
  multiset(multiset &&ms) noexcept;
  ~multiset();
  multiset operator=(multiset &&ms) noexcept;

  // Iterators
  iterator begin() const;
  iterator end() const;

  // Capacity
  bool empty();
  size_type Size();
  size_type max_size();
  size_type count(const Key &key);
  void clear();
  iterator insert(const value_type &value);

  // Modifiers
  void erase(iterator pos);
  void swap(multiset &other);
  void merge(multiset &other);
  bool contains(const Key &key);
  iterator find(const Key &key);
  std::pair<iterator, iterator> equal_range(const Key &key);
  iterator lower_bound(const Key &key);
  iterator upper_bound(const Key &key);
  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};
} // namespace s21

#include "s21_multiset.hpp"

#endif // S21_MULTISET_H
