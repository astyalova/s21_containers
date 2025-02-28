#ifndef S21_LIST_HPP
#define S21_LIST_HPP

#include "s21_list.h"

namespace s21 {

    template <class T>
    list<T>::list() : head_(nullptr), tail_(nullptr), node_size_(0) {}

    template <class T>
    list<T>::list(size_type n) : head_(nullptr), tail_(nullptr), node_size_(0) {
        for(int i = 0; i < n; ++i) {
            push_back(T()); // создает временный объект типа Т по умолчанию
            //по сути вызывает конструктор по умолчанию для типа Т
        }
    }

    template <class T>
    list<T>::list(std::initializer_list<value_type> const &items) : head_(nullptr), tail_(nullptr), node_size_(0) {
        for(const auto& item : items) {
            push_back(item);
        }
    }

    template <class T>
    list<T>::list(const list &l) : head_(nullptr), tail_(nullptr), node_size_(0)  {
        for (auto it = l.cbegin(); it != l.cend(); ++it) {
            push_back(*it);
        }
    }

    template <class T>
    list<T>::list(list &&l) {
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
        while(current_node != nullptr) {
            Node* temp = current_node->next;
            delete current_node;     
            current_node = temp;    
        }
    }

    template <class T>
    list<T> &list<T>::operator=(list &&l) {
        if(this != &l) {
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
        return head_->data_;
    }

    template <class T>
    typename list<T>::const_reference list<T>::back() const {
        return tail_->data_;
    }

    template <class T>
    typename list<T>::iterator list<T>::begin() {
        if(empty()) {
            return iterator(tail_->next);
        }
        return iterator(head_);
    }

    template <class T>
    typename list<T>::iterator list<T>::end() {
        return iterator(tail_->next);
    }

    template <class T>
    typename list<T>::const_iterator list<T>::cbegin() const {
        if(empty()) {
            return const_iterator(tail_->next);
        }
        return const_iterator(head_);
    }

    template <class T>
    typename list<T>::const_iterator list<T>::cend() const {
        return const_iterator(tail_->next);
    }

    template <class T>
    bool list<T>::empty() const {
        return node_size_ == 0;
    }

    template <class T>
    typename list<T>::size_type list<T>::size() const {
        return node_size_;
    }

    template <class T>
    typename list<T>::size_type list<T>::max_size() {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }

    template <class T>
    void list<T>::clear() {
        while(head_ != nullptr) {
            Node* temp = head_;
            head_ = head_->next;
            delete temp;
        }
        tail_ = nullptr;
        node_size_ = 0;
    }

//insert before it
    template <class T>
    typename list<T>::iterator list<T>::insert(iterator pos, const_reference value) {

        if(pos == cend() || empty()) {
            push_back(value);
            ++node_size_;
            return iterator(tail_);
        }

        Node* temp = new Node(value);

        if(pos == cbegin()) {
            temp->next = head_;
            head_->prev = temp;
            temp = head_;

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

//return next node it
    template <class T>
    typename list<T>::iterator list<T>::erase(iterator pos) {

        if (pos == cend()) {
            throw std::out_of_range("list::erase(): cannot erase end() iterator"); //pos !=cend() нельзя разыменовать 
        }

        Node* current_node = pos.getNode();

        if(pos == cbegin()) {
            head_ = current_node->next;
            if (head_)  { //если один элемент был
                head_->prev = nullptr;
            }

        } else if(current_node == tail_) {
            tail_ = current_node->prev;
            if (tail_)  { //сейм
                tail_->next = nullptr;
            }
        } else {

        Node* next = current_node->next;
        current_node->next->prev = current_node->prev;
        current_node->prev->next = current_node->next;
        delete current_node;

        }
        --node_size_;
        return head_ ? iterator(head_) : cend();

    }

    template <class T>
    void list<T>::push_back(const_reference value) {
        Node* new_node = new Node(value);
        if(empty()) {
            head_ = new_node;
            tail_ = new_node;
        } else {
            tail_->next = new_node;
            tail_ = new_node;
        }
        ++node_size_;
    }

    template <class T>
    void list<T>::pop_back() {
        if(!empty()) {
            if(node_size_ == 1) {
                delete tail_;
                head_ = tail_ = nullptr;
            } else {
                Node* prevnode = tail_->prev;
                delete tail_;
                tail_ = prevnode;
                tail_->next = nullptr;
            }
        }
        --node_size_;
    }

    template <class T>
    void list<T>::push_front(const_reference value) {
        Node* new_node = new Node(value);

        if(empty()) {
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
        if(!empty()) {
            if(node_size_ == 1) {
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

    template <class T>
    void list<T>::swap(list &other) {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(node_size_, other.node_size_);
    }

    template <class T>
    void list<T>::merge(list &other) {
        other.sort();
        this->sort();

        if(*other.head < *head_) {
            other.head_->next = head_;
            head_ = other.head_;
            other.head_ = nullptr;
        }

        Node* other_current_node = other.head_;
        Node* current_node = head_;

        while(current_node->next != nullptr && other_current_node->next != nullptr) {
        if (*other_current_node < *current_node) {
            Node* nextnode = current_node;
            Node* to_insert = other_current_node;

            other_current_node = other_current_node->next;

            to_insert->next = nextnode;
            to_insert->prev = nextnode->prev;

            if (nextnode->prev != nullptr) {
                nextnode->prev->next = to_insert;
            } else {
                head_ = to_insert; //insert before head_
            }
            nextnode->prev = to_insert;
        } else {
            current_node = current_node->next;
        }
    }

        if(other_current_node != nullptr) {
            tail_->next = other_current_node;
            other_current_node->prev = tail_;
            tail_ = other.tail_;
        }

        node_size_ += other.node_size_;
        other.node_size_ = 0;
        other.head_ = nullptr;
        other.tail_ = nullptr;
    }

//insert another list before pos;
    template <class T>
    void list<T>::splice(iterator pos, list& other) {
        Node* pos_node = pos.getNode();
        if(empty()) {
            head_ = other.head_;
            tail_ = other.tail_;
        } else if (pos_node == head_) { //insert other list in the begin of this
            other.tail_->next = head_;
            head_->prev = other.tail_;
            head_ = other.head_;
        } else { //
            other.tail_->next = pos_node;
            pos_node->prev->next = other.head_;
            other.head_->prev = pos_node->prev;
            pos_node->prev = other.tail_;
        }
        node_size_ += other.node_size_;
        other.node_size_ = 0;
        other.head_ = nullptr; //other is empty after splice;
        other.tail_ = nullptr;
    }

//head -> head->next
// head->prev -> nullptr
    template <class T>
    void list<T>::reverse() {
        Node* current_node = head_;
        Node* temp = nullptr;

        while(current_node != nullptr) {
            temp = current_node->prev;
            current_node->prev = current_node->next;
            current_node->next = temp;
            current_node = current_node->prev;
        }

        if(temp != nullptr) {
            head_ = temp->prev;
        }

        tail_ = head_;
    }

    template <class T>
    void list<T>::unique() {
        if(!empty()) {
            Node* current_node = head_;
            while(current_node->next != nullptr) {
                Node* nextnode = current_node->next;
                if(*current_node->next == *current_node) {
                    erase(iterator(nextnode));
                    --node_size_;
                }
                current_node = nextnode;
            }
        }
    }


    template <class T>
    void list<T>::sort() {
        if(node_size_ > 1) {
            bool swapped = true;
            while(swapped) {
                swapped = false;
                Node* current_node = head_;
                while(current_node->next != nullptr) {
                    if(*current_node->next < *current_node) {
                        std::swap(current_node->next->data_, current_node->data_);
                        swapped = true;
                    }
                    current_node = current_node->next;
                }
            }
        }
    }
}; //namespace s21


#endif