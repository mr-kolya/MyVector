#include <cmath>
#include <iostream>
#include "vector.h"
Vector::Iterator::Iterator() : iterator_(nullptr) {
}

Vector::Iterator::Iterator(Vector::ValueType *pointer) : iterator_(pointer) {
}

Vector::ValueType &Vector::Iterator::operator*() const {
    return *iterator_;
}

Vector::ValueType *Vector::Iterator::operator->() const {
    return iterator_;
}

Vector::Iterator &Vector::Iterator::operator=(Vector::Iterator other) {
    iterator_ = other.iterator_;
    return *this;
}

Vector::Iterator &Vector::Iterator::operator++() {
    ++iterator_;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
    Vector::Iterator result = *this;
    ++iterator_;
    return result;
}

Vector::Iterator &Vector::Iterator::operator--() {
    --iterator_;
    return *this;
}

Vector::Iterator Vector::Iterator::operator--(int) {
    Vector::Iterator result = *this;
    --iterator_;
    return result;
}

Vector::Iterator Vector::Iterator::operator+(Vector::DifferenceType shift) {
    return Iterator(iterator_ + shift);
}

Vector::DifferenceType Vector::Iterator::operator-(Vector::Iterator other) {
    return iterator_ - other.iterator_;
}

Vector::Iterator &Vector::Iterator::operator+=(Vector::DifferenceType shift) {
    iterator_ += shift;
    return *this;
}

Vector::Iterator &Vector::Iterator::operator-=(Vector::DifferenceType shift) {
    return *this += -shift;
}

bool Vector::Iterator::operator==(const Vector::Iterator &other) const {
    return iterator_ == other.iterator_;
}

bool Vector::Iterator::operator!=(const Vector::Iterator &other) const {
    return !(*this == other);
}

std::strong_ordering Vector::Iterator::operator<=>(const Iterator &other) const {
    if (iterator_ == other.iterator_) {
        return std::strong_ordering::equal;
    } else if (iterator_ < other.iterator_) {
        return std::strong_ordering::less;
    } else {
        return std::strong_ordering::greater;
    }
}

Vector::Vector() : begin_(), size_(0), capacity_(0) {
}

Vector::Vector(size_t size) {
    try {
        size_ = size;
        capacity_ = size;
        begin_ = new ValueType[capacity_];
        for (size_t i = 0; i < size; ++i) {
            begin_[i] = 0;
        }
    } catch (std::bad_alloc &error) {
        std::cout << error.what() << std::endl;
        std::terminate();
    }
}

Vector::Vector(std::initializer_list<ValueType> list) {
    try {
        size_ = list.size();
        capacity_ = list.size();
        begin_ = new ValueType[capacity_];
        size_t i = 0;
        for (auto value_list : list) {
            begin_[i] = value_list;
            ++i;
        }
    } catch (std::bad_alloc &error) {
        std::cout << error.what() << std::endl;
        std::terminate();
    }
}

Vector::Vector(const Vector &other) {
    try {
        size_ = other.size_;
        capacity_ = other.capacity_;
        begin_ = new ValueType[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            begin_[i] = other.begin_[i];
        }
    } catch (std::bad_alloc &error) {
        std::cout << error.what() << std::endl;
        std::terminate();
    }
}

Vector &Vector::operator=(const Vector &other) {
    try {
        size_ = other.size_;
        capacity_ = other.capacity_;
        delete[] begin_;
        begin_ = new ValueType[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            begin_[i] = other.begin_[i];
        }
        return *this;
    } catch (std::bad_alloc &error) {
        std::cout << error.what() << std::endl;
        std::terminate();
    }
}

Vector::~Vector() {
    delete[] begin_;
}

Vector::SizeType Vector::Size() const {
    return size_;
}

Vector::SizeType Vector::Capacity() const {
    return capacity_;
}

const Vector::ValueType *Vector::Data() const {
    return &begin_[0];
}

Vector::ValueType &Vector::operator[](size_t position) {
    return this->begin_[position];
}

Vector::ValueType Vector::operator[](size_t position) const {
    return this->begin_[position];
}

bool Vector::operator==(const Vector &other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (size_t i = 0; i < size_; ++i) {
        if (begin_[i] != other[i]) {
            return false;
        }
    }
    return true;
}

bool Vector::operator!=(const Vector &other) const {
    return !(*this == other);
}

std::strong_ordering Vector::operator<=>(const Vector &other) const {
    if (other == *this) {
        return std::strong_ordering::equal;
    }
    for (size_t i = 0; i < fmin(other.size_, size_); ++i) {
        if (other.begin_[i] != begin_[i]) {
            if (begin_[i] < other.begin_[i]) {
                return std::strong_ordering::less;
            } else {
                return std::strong_ordering::greater;
            }
        }
    }
    if (size_ < other.size_) {
        return std::strong_ordering::less;
    } else {
        return std::strong_ordering::greater;
    }
}

void Vector::Reserve(Vector::SizeType new_capacity) {
    if (capacity_ >= new_capacity) {
        return;
    }
    try {
        Vector past_this_vector(*this);
        capacity_ = new_capacity;
        delete[] begin_;
        begin_ = new ValueType[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            begin_[i] = past_this_vector[i];
        }
    } catch (std::bad_alloc &error) {
        std::cout << error.what() << std::endl;
        std::terminate();
    }
}

void Vector::Clear() {
    size_ = 0;
}

void Vector::PushBack(const Vector::ValueType &new_element) {
    if (size_ + 1 > capacity_) {
        if (capacity_ == 0) {
            this->Reserve(1);
        } else {
            this->Reserve(2 * capacity_);
        }
    }
    this->begin_[size_] = new_element;
    ++size_;
}

void Vector::PopBack() {
    --size_;
}

void Vector::Swap(Vector &other) {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(begin_, other.begin_);
}

Vector::Iterator Vector::Begin() {
    return Iterator(&begin_[0]);
}

Vector::Iterator Vector::begin() {
    return this->Begin();
}

Vector::Iterator Vector::End() {
    return this->begin() + size_;
}

Vector::Iterator Vector::end() {
    return this->End();
}