#ifndef S21_LIST_TPP
#define S21_LIST_TPP

#include "s21_list.h"

namespace s21 {
template <class T>
list<T>::list() : head_(nullptr), tail_(nullptr), node_size_(0) {}

template <class T>
list<T>::list(size_type n) : head_(nullptr), tail_(nullptr), node_size_(0) {
  for (int i = 0; i < n; ++i) {
    push_back(T());  // создает временный объект типа Т по умолчанию
    // по сути вызывает конструктор по умолчанию для типа Т
  }
}

template <class T>
list<T>::list(std::initializer_list<value_type> const& items)
    : head_(nullptr), tail_(nullptr), node_size_(0) {
  for (const auto& item : items) {
    push_back(item);
  }
}

template <class T>
list<T>::list(const list& l) : head_(nullptr), tail_(nullptr), node_size_(0) {
  for (auto it = l.cbegin(); it != l.cend(); ++it) {
    push_back(*it);
  }
}

template <class T>
list<T>::list(list&& l) {
  head_ = l.head_;
  tail_ = l.tail_;
  node_size_ = l.node_size_;

  l.head_ = nullptr;
  l.tail_ = nullptr;
  l.node_size_ = 0;
}

template <class T>
list<T>::~list() {
  Node* current_node = head_;
  while (current_node != nullptr) {
    Node* temp = current_node->next;
    delete current_node;
    current_node = temp;
  }
}

template <class T>
list<T>& list<T>::operator=(list&& l) {
  if (this != &l) {
    clear();

    head_ = l.head_;
    tail_ = l.tail_;
    node_size_ = l.node_size_;

    l.head_ = nullptr;
    l.tail_ = nullptr;
    l.node_size_ = 0;
  }

  return *this;
}
template <class T>
typename list<T>::const_reference list<T>::front() {
  return head_->data;
}

template <class T>
typename list<T>::const_reference list<T>::back() {
  return tail_->data;
}

template <class T>
typename list<T>::iterator list<T>::begin() {
  if (empty()) {
    return iterator(end());
  }
  return iterator(head_);
}

template <class T>
typename list<T>::iterator list<T>::end() {
  return iterator(tail_->next);
}

template <class T>
typename list<T>::const_iterator list<T>::cbegin() const {
  return const_iterator(head_);
}

template <class T>
typename list<T>::const_iterator list<T>::cend() const {
  return const_iterator(tail_->next);
}

template <typename T>
bool list<T>::empty() {
  return node_size_ == 0;
}

template <typename T>
typename list<T>::size_type list<T>::size() {
  return node_size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <class T>
void list<T>::clear() {
  while (head_ != nullptr) {
    Node* temp = head_;
    head_ = head_->next;
    delete temp;
  }
  tail_ = nullptr;
  node_size_ = 0;
}

template <class T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  if (pos == end() || empty()) {
    push_back(value);
    ++node_size_;
    return iterator(tail_);
  }

  Node* temp = new Node(value);

  if (pos == begin()) {
    temp->next = head_;
    head_->prev = temp;
    head_ = temp;

  } else {
    Node* current_node = pos.getNode();
    temp->next = current_node;
    temp->prev = current_node->prev;
    current_node->prev->next = temp;
    current_node->prev = temp;
  }

  ++node_size_;
  return iterator(temp);
}

template <typename T>
void list<T>::erase(iterator pos) {
  Node* current_node = pos.getNode();

  if (current_node == nullptr) {
    throw std::out_of_range("Iterator is out of range");
  }
  if (current_node == head_) {
    head_ = head_->next;
    if (head_ != nullptr) {
      head_->prev = nullptr;
    }
  } else if (current_node == tail_) {
    tail_ = tail_->prev;
    tail_->next = nullptr;
  } else {
    current_node->prev->next = current_node->next;
    current_node->next->prev = current_node->prev;
  }

  delete current_node;
  --node_size_;
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node* new_node = new Node(value);
  if (empty()) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    new_node->prev = tail_;
    tail_->next = new_node;
    tail_ = new_node;
  }
  ++node_size_;
}

template <typename T>
void list<T>::pop_back() {
  if (!empty()) {
    if (head_ == tail_) {
      clear();
    } else {
      Node* new_tail = tail_;
      tail_ = tail_->prev;
      tail_->next = nullptr;
      delete new_tail;
      node_size_--;
    }
  }
}

template <class T>
void list<T>::push_front(const_reference value) {
  Node* new_node = new Node(value);

  if (empty()) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    new_node->next = head_;
    head_->prev = new_node;
    head_ = new_node;
  }
  ++node_size_;
}

template <class T>
void list<T>::pop_front() {
  if (!empty()) {
    if (node_size_ == 1) {
      delete tail_;
      head_ = tail_ = nullptr;
    } else {
      Node* nextnode = head_->next;
      delete head_;
      head_ = nextnode;
      head_->prev = nullptr;
    }
    --node_size_;
  }
}

template <typename T>
void list<T>::swap(list& other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(node_size_, other.node_size_);
}

template <class T>
void list<T>::splice(iterator pos, list& other) {
    if (pos != end()) {
        Node* pos_node = pos.getNode();
        if (pos_node == head_) {  // insert other list in the begin of this
            other.tail_->next = head_;
            head_->prev = other.tail_;
            head_ = other.head_;
        } else {  
            if (other.tail_ != nullptr && pos_node != nullptr) {
                other.tail_->next = pos_node;
                Node* prev_pos_node = pos_node->prev;
                pos_node->prev = other.tail_;
                prev_pos_node->next = other.head_;
                other.head_->prev = prev_pos_node;

                if (pos_node == tail_) {
                    tail_ = other.tail_;
                }
            }
        }
        node_size_ += other.node_size_;
        other.node_size_ = 0;
        other.head_ = nullptr;  // other is empty after splice;
        other.tail_ = nullptr;
    }
}

template <class T>
void list<T>::merge(list& other) {
    other.sort(); 
    this->sort();

    Node* this_node = head_;
    Node* other_node = other.head_;

    while (this_node->next && other_node) { 
        if (other_node->data < this_node->next->data) {
            Node* temp = other_node;
            other_node = other_node->next;
            temp->next = this_node->next;
            temp->prev = this_node;
            if (this_node->next) {
                this_node->next->prev = temp;
            }
            this_node->next = temp;
        } else {
            this_node = this_node->next;
        }
    }

    if (other_node) { 
        tail_->next = other_node;
        other_node->prev = tail_;
        tail_ = other.tail_;
    }

    node_size_ += other.node_size_; 
    other.head_ = other.tail_ = nullptr;
    other.node_size_ = 0;
}


template <class T>
void list<T>::reverse() {
  Node* current_node = head_;
  Node* temp = nullptr;

  while (current_node != nullptr) {
    temp = current_node->prev;
    current_node->prev = current_node->next;
    current_node->next = temp;
    current_node = current_node->prev;
  }

  Node* tmp = head_;
  head_ = tail_;
  tail_ = tmp;
}

template <class T>
void list<T>::unique() {
  if (!empty()) {
    Node* current_node = head_;
    while (current_node->next != nullptr) {
      Node* next_node = current_node->next;
      if (*next_node == *current_node) {
        erase(iterator(next_node));
      } else {
        current_node = next_node;
      }
    }
  }
}

template <class T>
void list<T>::sort() {
  if (node_size_ > 1) {
    bool swapped = true;
    while (swapped) {
      swapped = false;
      Node* current_node = head_;
      while (current_node->next != nullptr) {
        if (*current_node->next < *current_node) {
          std::swap(current_node->next->data, current_node->data);
          swapped = true;
        }
        current_node = current_node->next;
      }
    }
  }
}

}  // namespace s21

#endif