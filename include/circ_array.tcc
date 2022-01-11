
#include "circ_array.h"
#include <stdexcept>

namespace cs225 {

template <class T>
circ_array<T>::circ_array() : capacity_{0}, front_{-1}, rear_{-1}, size_{0} {
  arr_ = std::make_unique<T[]>(capacity_);
}

template <class T> circ_array<T>::circ_array(uint64_t size) {

  capacity_ = size;
  size_ = capacity_;
  arr_ = std::make_unique<T[]>(capacity_);
  if (size_ > 0) {
    front_ = 0;
    rear_ = size_ - 1;
  }
]}

template <class T> circ_array<T>::circ_array(const circ_array &other) {
  capacity_ = other.capacity_;
  size_ = other.size_;
  front_ = other.front_;
  rear_ = other.rear_;
  arr_ = std::make_unique<T[]>(capacity_);
  for (uint64_t i = 0; i <= other.capacity_; i++) {
    arr_[i] = std::move(other.arr_[i]);
  }
}

template <class T>
circ_array<T>::circ_array(circ_array &&other)
    : arr_{nullptr}, capacity_{0}, size_{0} {
  swap(other);
}

template <class T> circ_array<T> &circ_array<T>::operator=(circ_array rhs) {
  swap(rhs);
  return *this;
}

template <class T> circ_array<T>::~circ_array() = default;

template <class T> void circ_array<T>::swap(circ_array &other) {
  std::swap(capacity_, other.capacity_);
  std::swap(arr_, other.arr_);
  std::swap(size_, other.size_);
  std::swap(front_, other.front_);
  std::swap(rear_, other.rear_);
}

template <class T> const T &circ_array<T>::operator[](uint64_t idx) const {
  idx = (front_ + idx) % capacity_;
  return arr_[idx];
}

template <class T> T &circ_array<T>::operator[](uint64_t idx) {
  idx = (front_ + idx) % capacity_;
  return arr_[idx];
}

template <class T> const T &circ_array<T>::at(uint64_t idx) const {
  idx = (front_ + idx) % capacity_;
  return arr_[idx];
}

template <class T> T &circ_array<T>::at(uint64_t idx) {
  idx = (front_ + idx) % capacity_;

  return arr_[idx];
}

template <class T> void circ_array<T>::push_front(T elem) {
  if (size_ == capacity_) {
    resize_capacity();
  }
  if (front_ == -1) {
    front_ = 0;
    rear_ = 0;
  } else {
    if (front_ == 0) {

      front_ = capacity_ - 1;
    } else {
      --front_;
    }
  }
  arr_[front_] = std::move(elem);
  ++size_;
}

template <class T> void circ_array<T>::push_back(T elem) {
  if (size_ == capacity_) {
    resize_capacity();
  }
  rear_ = (front_ + size_) % capacity_;
  arr_[rear_] = std::move(elem);
  ++size_;
}

template <class T> void circ_array<T>::pop_front() {
  front_ = (1 + front_) % capacity_;
  --size_;
}

template <class T> void circ_array<T>::pop_back() {
  if (rear_ == 0) {
    rear_ = capacity_ - 1;
  } else {
    --rear_;
  }
  --size_;
}

template <class T> void circ_array<T>::erase(uint64_t idx) {
  idx = (front_ + idx) % capacity_;
  for (uint64_t i = idx; i < (size_ + front_) % capacity_;
       i = (i + 1) % capacity_) {
    arr_[i] = arr_[(i + 1) % capacity_];
  }
  --size_;
}

template <class T> uint64_t circ_array<T>::size() const {
  return size_;
}

template <class T> bool circ_array<T>::empty() const {
  if (size_ == 0) {
    return true;
  }
  return false;
}
template <class T> void circ_array<T>::resize_capacity() {
  if (capacity_ == 0) {
    capacity_ = 2;
  }
  capacity_ = 2 * capacity_;
  auto temp = std::make_unique<T[]>(capacity_);
  for (uint64_t i = 0; i < capacity_; i++) {
    temp[i] = std::move(arr_[i]);
  }
  std::swap(arr_, temp);
}
} // namespace cs225