#ifndef S21_TREE_HPP
#define S21_TREE_HPP

#include "s21_tree.h"

namespace s21 {
template <typename T, typename K>
BSTree<T, K>::BSTree() : root_(nullptr), size_(0) {}

template <typename T, typename K>
BSTree<T, K>::BSTree(std::initializer_list<value_type> const &items)
    : root_(nullptr), size_(0) {
  for (const auto &item : items) {
    insert(item.first, item.second);
  }
}

template <typename T, typename K>
BSTree<T, K>::BSTree(const BSTree &other) : root_(nullptr), size_(0) {
  assign(other);
}

template <typename T, typename K>
BSTree<T, K>::BSTree(BSTree &&other) noexcept : size_(0) {
  root_ = other.root_;
  size_ = other.size_;

  other.root_ = nullptr;
  other.size_ = 0;
}

template <typename T, typename K> BSTree<T, K>::~BSTree() {
  clear();
  root_ = nullptr;
  size_ = 0;
}

template <typename T, typename K>
BSTree<T, K> &BSTree<T, K>::operator=(BSTree &&other) noexcept {
  if (this != &other) {
    clear(root_);
    root_ = other.root_;
    size_ = other.size_;
    other.root_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename T, typename K>
BSTree<T, K>::Iterator::Iterator() : ptr_(nullptr) {}

template <typename T, typename K>
BSTree<T, K>::Iterator::Iterator(Node *ptr) : ptr_(ptr) {}

template <typename T, typename K>
typename BSTree<T, K>::Iterator &BSTree<T, K>::Iterator::operator++() {
  if (!ptr_)
    return *this;

  if (ptr_->right) {
    ptr_ = ptr_->right;
    while (ptr_->left)
      ptr_ = ptr_->left;
  } else {
    Node *parent = ptr_->parent;
    while (parent && ptr_ == parent->right) {
      ptr_ = parent;
      parent = parent->parent;
    }
    ptr_ = parent;
  }
  return *this;
}

template <typename T, typename K>
typename BSTree<T, K>::Iterator BSTree<T, K>::Iterator::operator++(int) {
  Iterator temp(ptr_);
  ++(*this);
  return temp;
}

template <typename T, typename K>
typename BSTree<T, K>::map_type BSTree<T, K>::Iterator::operator*() const {
  if constexpr (std::is_same_v<T, K>) {
    return ptr_->key; // For Set, return the key as both key and value are same
  } else {
    return ptr_->value; // For Map, return the value
  }
}

template <typename T, typename K>
bool BSTree<T, K>::Iterator::operator==(Iterator other) const {
  return other.ptr_ == this->ptr_;
}

template <typename T, typename K>
bool BSTree<T, K>::Iterator::operator!=(Iterator other) const {
  return other.ptr_ != this->ptr_;
}

template <typename T, typename K>
typename BSTree<T, K>::Node *BSTree<T, K>::Iterator::operator->() const {
  return ptr_;
}

template <typename T, typename K>
typename BSTree<T, K>::iterator BSTree<T, K>::begin() const {
  Node *node = root_;
  while (node && node->left)
    node = node->left;
  return iterator(node);
}

template <typename T, typename K>
typename BSTree<T, K>::iterator BSTree<T, K>::end() const {
  return iterator(nullptr);
}

template <typename T, typename K> bool BSTree<T, K>::empty() {
  return size_ == 0;
}

template <typename T, typename K>
typename BSTree<T, K>::size_type BSTree<T, K>::size() {
  return size_;
}

template <typename T, typename K>
typename BSTree<T, K>::size_type BSTree<T, K>::max_size() {
  return std::numeric_limits<typename BSTree<K, T>::size_type>::max() /
         sizeof(typename BSTree<K, T>::value_type);
}

template <typename T, typename K> void BSTree<T, K>::clear() {
  clear(root_);
  root_ = nullptr;
  size_ = 0;
}

template <typename T, typename K> void BSTree<T, K>::clear(Node *node) {
  if (node) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

template <typename T, typename K>
typename BSTree<T, K>::size_type BSTree<T, K>::count(const key_type &key) {
  size_type count = 0;
  Node *current = root_;

  // Find the first occurrence
  while (current != nullptr) {
    if (key == current->key) {
      count++;
      // Check right subtree for duplicates
      Node *right = current->right;
      while (right && right->key == key) {
        count++;
        right = right->right;
      }
      // Check left subtree for duplicates
      Node *left = current->left;
      while (left && left->key == key) {
        count++;
        left = left->left;
      }
      break;
    } else if (key < current->key) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return count;
}

template <typename T, typename K>
typename BSTree<T, K>::iterator BSTree<T, K>::find(const key_type &key) {
  Node *current = root_;
  while (current) {
    if (key == current->key) {
      return iterator(current);
    } else if (key < current->key) {
      current = current->left;
    } else if (key > current->key) {
      current = current->right;
    }
  }
  return end();
}

template <typename T, typename K>
typename BSTree<T, K>::iterator BSTree<T, K>::insert(const K &key) {
  Node *new_node =
      new Node(key, key); // For set/multiset where key is the value
  Node *current = root_;
  Node *parent = nullptr;

  while (current != nullptr) {
    parent = current;
    if (key < current->key) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  new_node->parent = parent;
  if (parent == nullptr) {
    root_ = new_node;
  } else if (key < parent->key) {
    parent->left = new_node;
  } else {
    parent->right = new_node;
  }

  size_++;
  return iterator(new_node);
}

template <typename T, typename K>
std::pair<typename BSTree<T, K>::iterator, bool>
BSTree<T, K>::insert(const key_type &key, const map_type &obj) {
  if (!root_) {
    root_ = new Node(key, obj);
    ++size_;
    return {iterator(root_), true};
  }
  Node *current = root_;
  Node *parent = nullptr;

  while (current) {
    parent = current;
    if (key == current->key) {
      return {iterator(current), false};
    } else if (key < current->key) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  Node *new_node = new Node(key, obj);
  new_node->parent = parent;

  if (key < parent->key) {
    parent->left = new_node;
  } else {
    parent->right = new_node;
  }

  ++size_;

  // Балансировка от родителя нового узла до корня
  Node *balance_node = parent;
  while (balance_node) {
    balance_node->height = getHeight(balance_node);
    Node *balanced = balance(balance_node);

    // Обновляем корень если необходимо
    if (balanced->parent == nullptr) {
      root_ = balanced;
    }

    balance_node = balanced->parent;
  }

  return {iterator(new_node), true};
}

template <typename T, typename K>
std::pair<typename BSTree<T, K>::iterator, bool>
BSTree<T, K>::insert_or_assign(const key_type &key, const map_type &obj) {
  auto it = this->find(key);

  if (it != end()) {
    it->value = obj;
    return {iterator(it), true};
  }

  Node *current = root_;
  current = new Node(key, obj);
  ++size_;

  if (!root_) {
    root_ = current;
  } else {
    Node *parent = nullptr;
    Node *insertPos = root_;
    while (insertPos) {
      parent = insertPos;
      if (key < insertPos->key) {
        insertPos = insertPos->left;
      } else {
        insertPos = insertPos->right;
      }
    }

    if (key < parent->key) {
      parent->left = current;
    } else {
      parent->right = current;
    }

    current->parent = parent;
  }

  Node *insertedNode = current;
  while (insertedNode) {
    insertedNode = balance(insertedNode);
    insertedNode = insertedNode->parent;
  }

  return {iterator(current), true};
}

template <typename T, typename K> void BSTree<T, K>::erase(iterator pos) {
  if (!pos.ptr_)
    return;

  Node *node = pos.ptr_;
  Node *parent = node->parent;

  // Case 1: Node is a leaf
  if (!node->left && !node->right) {
    if (parent) {
      if (parent->left == node) {
        parent->left = nullptr;
      } else {
        parent->right = nullptr;
      }
    } else {
      root_ = nullptr;
    }
    delete node;
  }
  // Case 2: Node has one child
  else if (!node->left || !node->right) {
    Node *child = node->left ? node->left : node->right;

    if (parent) {
      if (parent->left == node) {
        parent->left = child;
      } else {
        parent->right = child;
      }
      child->parent = parent;
    } else {
      root_ = child;
      child->parent = nullptr;
    }
    delete node;
  }
  // Case 3: Node has two children
  else {
    // Find successor (minimum in right subtree)
    Node *successor = node->right;
    Node *successorParent = node;

    while (successor->left) {
      successorParent = successor;
      successor = successor->left;
    }

    // Copy successor's data
    node->key = successor->key;
    node->value = successor->value;

    // Remove successor
    if (successorParent == node) {
      successorParent->right = successor->right;
      if (successor->right)
        successor->right->parent = successorParent;
    } else {
      successorParent->left = successor->right;
      if (successor->right)
        successor->right->parent = successorParent;
    }

    delete successor;
  }

  --size_;

  // Rebalance the tree starting from the parent
  while (parent) {
    parent->height = getHeight(parent);
    parent = balance(parent);
    parent = parent->parent;
  }
}

template <typename T, typename K> void BSTree<T, K>::swap(BSTree &other) {
  BSTree temp(other);
  other.clear();
  other.assign(*this);
  BSTree<K, T>::clear();
  assign(temp);
  temp.clear();
}

template <typename T, typename K>
void BSTree<T, K>::assign(const BSTree &other) {
  for (auto i = other.begin(); i != other.end(); ++i)
    insert(i->key, i->value);
}

template <typename T, typename K> void BSTree<T, K>::merge(BSTree &other) {
  if (this != &other) {
    iterator it = other.begin();
    while (it != other.end()) {
      iterator current = it++;
      if (!contains(current->key)) {
        // Save the next node before potentially modifying the tree
        Node *next = (it != other.end()) ? it.ptr_ : nullptr;
        // Insert and transfer ownership
        insert(current->key, current->value);
        // Update iterator if needed
        if (next) {
          it = iterator(next);
        }
      }
    }
    // Clear other tree without deleting nodes we've transferred
    other.root_ = nullptr;
    other.size_ = 0;
  }
}

template <typename T, typename K>
bool BSTree<T, K>::contains(const key_type &key) {
  Node *current = root_;
  while (current) {
    if (key == current->key) {
      return true;
    } else if (key < current->key) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return false;
}

template <typename T, typename K>
std::pair<typename BSTree<T, K>::iterator, typename BSTree<T, K>::iterator>
BSTree<T, K>::equal_range(const key_type &key) {
  iterator lower = lower_bound(key);
  iterator upper = upper_bound(key);
  return std::make_pair(lower, upper);
}

// Returns an iterator to the first element whose key is not less than 'key'.
template <typename T, typename K>
typename BSTree<T, K>::iterator BSTree<T, K>::lower_bound(const key_type &key) {
  Node *current = root_;
  Node *best_candidate = nullptr;

  while (current) {
    if (current->key >= key) {
      best_candidate = current;
      current = current->left;
    } else {
      current = current->right;
    }
  }

  return best_candidate ? iterator(best_candidate) : end();
}

// Returns an iterator to the first element whose key is greater than 'key'.
template <typename T, typename K>
typename BSTree<T, K>::iterator BSTree<T, K>::upper_bound(const key_type &key) {
  Node *current = root_;
  Node *best_candidate = nullptr;

  while (current) {
    if (current->key > key) {
      best_candidate = current;
      current = current->left;
    } else {
      current = current->right;
    }
  }

  return best_candidate ? iterator(best_candidate) : end();
}

template <typename T, typename K>
typename BSTree<T, K>::map_type &BSTree<T, K>::at(const key_type &key) {
  Node *current = root_;
  while (current) {
    if (key == current->key) {
      return current->value;
    } else if (key < current->key) {
      current = current->left;
    } else if (key > current->key) {
      current = current->right;
    }
  }
  throw std::out_of_range("This key doesnt exist");
}

template <typename T, typename K>
typename BSTree<T, K>::map_type &BSTree<T, K>::operator[](const key_type &key) {
  Node *current = root_;
  // Search for existing key
  while (current) {
    if (key == current->key) {
      return current->value;
    } else if (key < current->key) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  // Create new node if key doesn't exist
  Node *new_node = new Node(key, map_type());
  ++size_;
  if (!root_) {
    root_ = new_node;
  } else {
    Node *parent = nullptr;
    Node *insert_pos = root_;

    // Find insertion position
    while (insert_pos) {
      parent = insert_pos;
      if (key < insert_pos->key) {
        insert_pos = insert_pos->left;
      } else {
        insert_pos = insert_pos->right;
      }
    }
    // Link new node
    new_node->parent = parent;
    if (key < parent->key) {
      parent->left = new_node;
    } else {
      parent->right = new_node;
    }
  }
  // Balance tree after insertion
  Node *balance_node = new_node;
  while (balance_node) {
    balance_node = balance(balance_node);
    balance_node = balance_node->parent;
  }
  return new_node->value;
}

template <typename T, typename K> int BSTree<T, K>::getHeight(Node *node) {
  if (!node)
    return 0;
  return 1 + std::max(getHeight(node->left), getHeight(node->right));
}

template <typename T, typename K>
int BSTree<T, K>::getBalanceFactor(Node *node) {
  if (!node)
    return 0;
  return getHeight(node->left) - getHeight(node->right);
}

template <typename T, typename K>
typename BSTree<T, K>::Node *BSTree<T, K>::smallRotateRight(Node *y) {
  Node *x = y->left;
  Node *T2 = x->right;
  Node *parent = y->parent;
  x->right = y;
  y->left = T2;

  x->parent = parent;
  y->parent = x;
  if (T2)
    T2->parent = y;

  // Обновляем родительские связи
  if (parent) {
    if (parent->left == y)
      parent->left = x;
    else
      parent->right = x;
  }

  y->height = getHeight(y);
  x->height = getHeight(x);

  return x;
}
template <typename T, typename K>
typename BSTree<T, K>::Node *BSTree<T, K>::smallRotateLeft(Node *x) {
  Node *y = x->right;
  Node *T2 = y->left;
  Node *parent = x->parent;

  y->left = x;
  x->right = T2;

  y->parent = parent;
  x->parent = y;
  if (T2)
    T2->parent = x;

  // update parents
  if (parent) {
    if (parent->left == x)
      parent->left = y;
    else
      parent->right = y;
  }

  x->height = getHeight(x);
  y->height = getHeight(y);

  return y;
}

template <typename T, typename K>
typename BSTree<T, K>::Node *BSTree<T, K>::bigRotateRight(Node *y) {
  y->left = smallRotateLeft(y->left);
  return smallRotateRight(y);
}

template <typename T, typename K>
typename BSTree<T, K>::Node *BSTree<T, K>::bigRotateLeft(Node *x) {
  x->right = smallRotateRight(x->right);
  return smallRotateLeft(x);
}

template <typename T, typename K>
typename BSTree<T, K>::Node *BSTree<T, K>::balance(Node *node) {
  if (!node)
    return nullptr;

  node->height = getHeight(node);

  int balance_factor = getBalanceFactor(node);

  // tree have balance
  if (std::abs(balance_factor) < 2) {
    return node;
  }

  // Left imbalance (>1)
  if (balance_factor > 1) {
    if (getBalanceFactor(node->left) < 0) {
      return bigRotateRight(node);
    } else {
      return smallRotateRight(node);
    }
  }

  // Right imbalance (< -1)
  if (balance_factor < -1) {
    if (getBalanceFactor(node->right) > 0) {
      return bigRotateLeft(node);
    } else {
      return smallRotateLeft(node);
    }
  }

  return node;
}
}; // namespace s21

#endif