#ifndef S21_VECTOR_HPP
#define S21_VECTOR_HPP

#include "s21_vector.h"

namespace s21 {

template <class T>
vector<T>::vector() : size_(0), capacity_(0), data_(nullptr) {}

template <class T>
vector<T>::vector(size_type n)
    : size_(n), capacity_(n), data_(new value_type[n]) {}

template <class T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : size_(items.size()), capacity_(items.size()),
      data_(new value_type[items.size()]) {
  std::copy(items.begin(), items.end(), data_);
}

template <class T>
vector<T>::vector(const vector &v)
    : size_(v.size_), capacity_(v.capacity_), data_(new value_type[v.size()]) {
  std::copy(v.data_, v.data_ + v.size_, data_);
}

template <class T>
vector<T>::vector(vector &&v) noexcept
    : size_(v.size_), capacity_(v.capacity_), data_(v.data_) {
  v.size_ = 0;
  v.capacity_ = 0;
  v.data_ = nullptr;
}

template <class T> vector<T>::~vector() {
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <class T> vector<T> &vector<T>::operator=(vector &&v) {
  if (this != &v) {
    delete[] data_;
    data_ = v.data_;
    size_ = v.size_;
    capacity_ = v.capacity_;

    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }
  return *this;
}

template <class T> typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[pos];
}

template <class T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return data_[pos];
}

template <class T> typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <class T> typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <class T> bool vector<T>::empty() const { return size_ == 0; }
template <class T> T *vector<T>::data() { return data_; }

template <class T> typename vector<T>::iterator vector<T>::begin() {
  return data_;
}

template <class T> typename vector<T>::iterator vector<T>::end() {
  return data_ + size_;
}

template <class T> void vector<T>::clear() {
  size_ = 0;
  capacity_ = 0;
  data_ = nullptr;
}

template <class T> typename vector<T>::const_reference vector<T>::front() {
  if (size_ == 0) {
    throw std::out_of_range("Vector is empty");
  }
  return data_[0];
}

template <class T> typename vector<T>::const_reference vector<T>::back() const {
  if (size_ == 0) {
    throw std::out_of_range("Vector is empty");
  }
  return data_[size_ - 1];
}

template <class T> typename vector<T>::size_type vector<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(T);
}
// увеличение емкости // резерв вызывается не только когда сайз больше, но и
// меньше, деструкторов должно быть столько, сколько объектов
template <class T> void vector<T>::reserve(size_type size) {
  if (size <= capacity_)
    return;
  if (size > max_size()) {
    throw std::length_error("Requested size exceeds max size");
  }

  std::unique_ptr<value_type[]> newdata(new value_type[size]);

  for (size_type i = 0; i < size_; ++i) {
    newdata[i] = std::move(data_[i]);
  }

  data_ = newdata.release(); // достаем из сырой памяти
  capacity_ = size;
}
template <class T> void vector<T>::shrink_to_fit() {
  if (size_ == capacity_) {
    return;
  }
  if (size_ < capacity_) {
    std::unique_ptr<value_type[]> newdata(new value_type[size_]);

    for (size_type i = 0; i < size_; ++i) {
      newdata[i] = std::move(data_[i]);
    }

    data_ = newdata.release();
    capacity_ = size_;
  }
}

template <class T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type idx = pos - data_;
  ++size_;

  std::unique_ptr<value_type[]> newdata(new value_type[size_]);

  for (size_type i = 0; i < idx; ++i) {
    newdata[i] = std::move(data_[i]);
  }

  newdata[idx] = value;

  for (size_type i = idx; i < size_ - 1; ++i) {
    newdata[i + 1] = std::move(data_[i]);
  }

  data_ = newdata.release();
  return data_ + idx;
}

template <class T> void vector<T>::erase(iterator pos) {
  size_type idx = pos - data_;
  // 1 начало диапазона переноса элементов//2конец диапазона переноса//3 на
  // какую позицию переносим
  std::move(data_ + idx + 1, data_ + size_, data_ + idx);
  --size_;
}

template <class T> void vector<T>::push_back(const_reference value) {
  if (capacity_ == size_) {
    size_type newcapacity = size_ * 2;
    reserve(newcapacity);
  }
  ++size_;
  if (size_ < capacity_) {
    std::unique_ptr<value_type[]> newdata(new value_type[size_]);

    for (size_type i = 0; i < size_; ++i) {
      newdata[i] = std::move(data_[i]);
    }

    newdata[size_ - 1] = value;
    data_ = newdata.release();
    capacity_ = size_;
  }
}

template <class T> void vector<T>::pop_back() {
  if (size_ > 0) {
    data_[size_ - 1].~T();
    --size_;
  }
}

template <class T> void vector<T>::swap(vector &other) {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(data_, other.data_);
}

template <class T>
template <class... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  vector<value_type> temp{args...};
  iterator cur_pos = begin() + (pos - begin());
  for (size_t i = 0; i < temp.size(); ++i) {
    cur_pos = insert(cur_pos, temp[i]);
    ++cur_pos;
  }
  return cur_pos;
}

template <class T>
template <class... Args>
void vector<T>::insert_many_back(Args &&...args) {
  for (const auto &arg : {args...}) {
    push_back(arg);
  }
}
}; // namespace s21

#endif