#ifndef __VECTOR__HPP__
#define __VECTOR__HPP__

#include "vector.h"

namespace g3 {

template <typename T, typename allocator>
Vector<T, allocator>::Vector() : 
    size_{0}, capacity_{0}, arr_{nullptr} 
{}

template <typename T, typename allocator>
Vector<T, allocator>::Vector(const Vector& rhv) : 
    size_{rhv.size_}, capacity_{rhv.capacity_}, arr_{alloc_.allocate(capacity_)} 
{}

template <typename T, typename allocator>
Vector<T, allocator>::Vector(Vector&& rhv) : 
    size_{rhv.size_}, capacity_{rhv.capacity_}, arr_{rhv.arr_} 
{
    rhv.size_ = 0;
    rhv.capacity_ = 0;
    rhv.arr_ = nullptr;
}

template <typename T, typename allocator>
Vector<T, allocator>::Vector(std::initializer_list<value_type> init) : 
    size_{init.size()}, capacity_{init.size()}, arr_{alloc_.allocate(init.size())}
{
    size_type i = 0;
    for(const_reference val : init)
    {
        alloc_.construct(arr_ + i, val);
        ++i;
    }
}

template <typename T, typename allocator>
Vector<T, allocator>::Vector(size_type size, const_reference val) : 
    size_{size}, capacity_{size}, arr_{alloc_.allocate(size)}
{
    for(size_type i = 0; i < size_; ++i)
    {
        alloc_.construct(arr_ + i, val);
    }
}

template <typename T, typename allocator>
template <typename InputIt>
Vector<T, allocator>::Vector(InputIt first, InputIt last) : 
    size_{std::distance(first, last)}, capacity_{size_}, arr_{alloc_.allocate(last - first)} 
{
    for(size_type i = 0; first != last; ++i)
    {
        alloc_.construct(arr_ + i, *first);
        ++first;
    }
}

template <typename T, typename allocator>
Vector<T, allocator>::~Vector() 
{
    clear();
}

template <typename T, typename allocator>
const Vector<T, allocator>& 
Vector<T, allocator>::operator=(const Vector& rhv) 
{
    if (this != &rhv) {
        clear();
        size_ = rhv.size_;
        capacity_ = rhv.capacity_;
        arr_ = alloc_.allocate(allocator(), capacity_);
        for(size_type i = 0; i < size_; ++i)
        {
            alloc_.construct(arr_ + i, rhv.arr_[i]);
        }
    }
    return *this;
}

template <typename T, typename allocator>
const Vector<T, allocator>& 
Vector<T, allocator>::operator=(Vector&& rhv)  
{
    if (this != &rhv) {
        clear();
        size_ = rhv.size_;
        capacity_ = rhv.capacity_;
        arr_ = rhv.arr_;
        rhv.size_ = 0;
        rhv.capacity_ = 0;
        rhv.arr_ = nullptr;
    }
    return *this;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::allocatortype 
Vector<T, allocator>::get_allocator() 
{
    return alloc_;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::reference 
Vector<T, allocator>::at(size_type pos) 
{
    if (pos >= size_) {
        throw std::out_of_range("Vector::at");
    }
    return arr_[pos];
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_reference 
Vector<T, allocator>::at(size_type pos) const 
{
    if (pos >= size_) {
        throw std::out_of_range("Vector::at");
    }
    return arr_[pos];
}

template <typename T, typename allocator>
typename Vector<T, allocator>::reference 
Vector<T, allocator>::operator[](size_type pos) 
{
    return arr_[pos];
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_reference 
Vector<T, allocator>::operator[](size_type pos) const 
{
    return arr_[pos];
}

template <typename T, typename allocator>
typename Vector<T, allocator>::reference 
Vector<T, allocator>::front() 
{
    return arr_[0];
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_reference 
Vector<T, allocator>::front() const 
{

    return arr_[0];
}

template <typename T, typename allocator>
typename Vector<T, allocator>::reference 
Vector<T, allocator>::back() 
{
    return arr_[size_ - 1];
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_reference 
Vector<T, allocator>::back() const 
{
    return arr_[size_ - 1];
}

template <typename T, typename allocator>
typename Vector<T, allocator>::iterator 
Vector<T, allocator>::begin() 
{
    return iterator(arr_);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_iterator 
Vector<T, allocator>::begin() const 
{
    return const_iterator(arr_);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_iterator 
Vector<T, allocator>::cbegin() const 
{
    return const_iterator(arr_);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::iterator Vector<T, allocator>::end() 
{
    return iterator(arr_ + size_);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_iterator 
Vector<T, allocator>::end() const 
{
    return const_iterator(arr_ + size_);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_iterator 
Vector<T, allocator>::cend() const 
{
    return const_iterator(arr_ + size_);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::iterator 
Vector<T, allocator>::rbegin() 
{
    return iterator(arr_ + size_ - 1);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_iterator 
Vector<T, allocator>::rbegin() const 
{
    return const_iterator(arr_ + size_ - 1);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_iterator 
Vector<T, allocator>::crbegin() const 
{
    return const_iterator(arr_ + size_ - 1);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::iterator 
Vector<T, allocator>::rend() 
{
    return iterator(arr_ - 1);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_iterator 
Vector<T, allocator>::rend() const 
{
    return const_iterator(arr_ - 1);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_iterator 
Vector<T, allocator>::crend() const 
{
    return const_iterator(arr_ - 1);
}

template <typename T, typename allocator>
bool Vector<T, allocator>::empty() const {
    return size_ == 0;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::size_type 
Vector<T, allocator>::size() const 
{
    return size_;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::size_type 
Vector<T, allocator>::capacity() const 
{
    return capacity_;
}

template <typename T, typename allocator>
void Vector<T, allocator>::reserve(size_type new_cap) {
    if (new_cap > capacity_) {
        pointer new_arr = alloc_.allocate(new_cap);

        for (size_type i = 0; i < size_; ++i) {
            alloc_.construct(new_arr + i, std::move(arr_[i]));
            alloc_.destroy(arr_ + i);
        }

        alloc_.deallocate(arr_, capacity_);
        arr_ = new_arr;
        capacity_ = new_cap;
    }
}

template <typename T, typename allocator>
void Vector<T, allocator>::clear() noexcept {
    for(size_type i = 0; i < size_; ++i)
    {
        alloc_.destroy(arr_ + i);
    }
    alloc_.deallocate(arr_, capacity_);
    size_ = 0;
    capacity_ = 0;
    arr_ = nullptr;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::iterator 
Vector<T, allocator>::insert(const_iterator pos, const_reference val) {
    size_type index = pos - begin();
    if (size_ == capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }

    iterator it = begin() + index;
    if (it != end()) {
        for (auto back = end(); back != it; --back) {
            alloc_.construct(&*(back), std::move(*(back - 1)));
            alloc_.destroy(&*(back - 1));
        }
    }

    alloc_.construct(arr_ + index, val);
    ++size_;
    return iterator(arr_ + index);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::iterator 
Vector<T, allocator>::insert(const_iterator pos, size_type count, const_reference val) {
    size_type index = pos - begin();
    if (size_ + count > capacity_) {
        reserve(std::max(capacity_ * 2, size_ + count));
    }

    iterator it = begin() + index;
    if (it != end()) {
        for (auto back = end() + count - 1; back != it + count - 1; --back) {
            alloc_.construct(&*back, std::move(*(back - count)));
            alloc_.destroy(&*(back - count));
        }
    }

    for (size_type i = 0; i < count; ++i) {
        alloc_.construct(arr_ + index + i, val);
    }

    size_ += count;
    return iterator(arr_ + index);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::iterator 
Vector<T, allocator>::insert(const_iterator pos, std::initializer_list<value_type> init) {
    size_type index = pos - begin();
    size_type count = init.size();
    if (size_ + count > capacity_) {
        reserve(std::max(capacity_ * 2, size_ + count));
    }

    iterator it = begin() + index;
    if (it != end()) {
        for (auto back = end() + count - 1; back != it + count - 1; --back) {
            alloc_.construct(&*back, std::move(*(back - count)));
            alloc_.destroy(&*(back - count));
        }
    }

    auto init_it = init.begin();
    for (size_type i = 0; i < count; ++i) {
        alloc_.construct(arr_ + index + i, *init_it++);
    }

    size_ += count;
    return iterator(arr_ + index);
}

template <typename T, typename allocator>
template <typename InputIt>
typename Vector<T, allocator>::iterator 
Vector<T, allocator>::insert(const_iterator pos, InputIt first, InputIt last) {
    size_type index = pos - begin();
    size_type count = std::distance(first, last);
    if (size_ + count > capacity_) {
        reserve(std::max(capacity_ * 2, size_ + count));
    }

    iterator it = begin() + index;
    if (it != end()) {
        for (auto back = end() + count - 1; back != it + count - 1; --back) {
            alloc_.construct(&*back, std::move(*(back - count)));
            alloc_.destroy(&*(back - count));
        }
    }

    for (size_type i = 0; first != last; ++i, ++first) {
        alloc_.construct(arr_ + index + i, *first);
    }

    size_ += count;
    return iterator(arr_ + index);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::iterator 
Vector<T, allocator>::erase(const_iterator pos) {
    size_type index = pos - begin();
    std::move(arr_ + index + 1, arr_ + size_, arr_ + index);
    arr_[size_ - 1].~value_type();
    --size_;
    return iterator(arr_ + index);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::iterator 
Vector<T, allocator>::erase(const_iterator first, const_iterator last) {
    size_type first_index = first - begin();
    size_type last_index = last - begin();
    size_type count = last_index - first_index;
    std::move(arr_ + last_index, arr_ + size_, arr_ + first_index);
    for (size_type i = 0; i < count; ++i) {
        arr_[size_ - 1 - i].~value_type();
    }
    size_ -= count;
    return iterator(arr_ + first_index);
}

template <typename T, typename allocator>
void Vector<T, allocator>::push_back(const_reference val) {
    insert(end(), val);
}

template <typename T, typename allocator>
void Vector<T, allocator>::pop_back() {
    erase(end() - 1);
}

template <typename T, typename allocator>
void Vector<T, allocator>::resize(size_type new_size, const_reference val) {
    if (new_size < size_) {
        for (size_type i = new_size; i < size_; ++i) {
            arr_[i].~value_type();
        }
    } else if (new_size > size_) {
        if (new_size > capacity_) {
            reserve(new_size);
        }
        for (size_type i = size_; i < new_size; ++i) {
            new (&arr_[i]) value_type(val);
        }
    }
    size_ = new_size;
}

template <typename T, typename allocator>
bool Vector<T, allocator>::operator==(const Vector& other) const 
{
    if (size_ != other.size_) return false;
    for (size_type i = 0; i < size_; ++i) {
        if (arr_[i] != other.arr_[i]) return false;
    }
    return true;
}

template <typename T, typename allocator>
bool Vector<T, allocator>::operator!=(const Vector& other) const 
{
    return !(*this == other);
}

template <typename T, typename allocator>
bool Vector<T, allocator>::operator<(const Vector& other) const 
{
    const_iterator it1 = begin();
    const_iterator it2 = other.begin();

    while (it1 != end() && it2 != other.end()) {
        if (*it1 < *it2) {
            return true;
        }
        if (*it2 < *it1) {
            return false;
        }
        ++it1;
        ++it2;
    }

    return (it1 == end()) && (it2 != other.end());
}

template <typename T, typename allocator>
bool Vector<T, allocator>::operator<=(const Vector& other) const 
{
    return !(other < *this);
}

template <typename T, typename allocator>
bool Vector<T, allocator>::operator>(const Vector& other) const {
    return other < *this;
}

template <typename T, typename allocator>
bool Vector<T, allocator>::operator>=(const Vector& other) const 
{
    return !(*this < other);
}

template <typename T, typename allocator>
int Vector<T, allocator>::compare(const Vector& other) const 
{
    if (*this < other) {
        return -1;
    }
    if (*this > other) {
        return 1;
    }
    return 0;
}


// ------ iterators ------

template <typename T, typename allocator>
Vector<T, allocator>::const_iterator::const_iterator(pointer ptr) :
    ptr(ptr) 
{}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_iterator 
Vector<T, allocator>::const_iterator::operator+(size_type n) const 
{
    return const_iterator(ptr + n);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_iterator 
Vector<T, allocator>::const_iterator::operator-(size_type n) const 
{
    return const_iterator(ptr - n);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_iterator& 
Vector<T, allocator>::const_iterator::operator++() 
{
    ++ptr;
    return *this;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_iterator 
Vector<T, allocator>::const_iterator::operator++(int) 
{
    const_iterator tmp = *this;
    ++ptr;
    return tmp;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_iterator& 
Vector<T, allocator>::const_iterator::operator--() 
{
    --ptr;
    return *this;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_iterator 
Vector<T, allocator>::const_iterator::operator--(int) 
{
    const_iterator tmp = *this;
    --ptr;
    return tmp;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_reference 
Vector<T, allocator>::const_iterator::operator*() const 
{
    return *ptr;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_pointer 
Vector<T, allocator>::const_iterator::operator->() const 
{
    return ptr;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_reference 
Vector<T, allocator>::const_iterator::operator[](size_type pos) const 
{
    return *(ptr + pos);
}

template <typename T, typename allocator>
bool Vector<T, allocator>::const_iterator::operator==(const const_iterator& other) const 
{
    return ptr == other.ptr;
}

template <typename T, typename allocator>
bool Vector<T, allocator>::const_iterator::operator!=(const const_iterator& other) const 
{
    return ptr != other.ptr;
}

template <typename T, typename allocator>
bool Vector<T, allocator>::const_iterator::operator<(const const_iterator& other) const 
{
    return ptr < other.ptr;
}

template <typename T, typename allocator>
bool Vector<T, allocator>::const_iterator::operator<=(const const_iterator& other) const 
{
    return ptr <= other.ptr;
}

template <typename T, typename allocator>
bool Vector<T, allocator>::const_iterator::operator>(const const_iterator& other) const 
{
    return ptr > other.ptr;
}

template <typename T, typename allocator>
bool Vector<T, allocator>::const_iterator::operator>=(const const_iterator& other) const 
{
    return ptr >= other.ptr;
}

template <typename T, typename allocator>
Vector<T, allocator>::iterator::iterator(pointer ptr) : 
    const_iterator(ptr) 
{}

template <typename T, typename allocator>
typename Vector<T, allocator>::iterator 
Vector<T, allocator>::iterator::operator+(size_type n) const 
{
    return iterator(this->ptr + n);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::iterator 
Vector<T, allocator>::iterator::operator-(size_type n) const 
{
    return iterator(this->ptr - n);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::iterator& 
Vector<T, allocator>::iterator::operator++() 
{
    ++this->ptr;
    return *this;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::iterator 
Vector<T, allocator>::iterator::operator++(int) 
{
    iterator tmp = *this;
    ++this->ptr;
    return tmp;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::iterator& 
Vector<T, allocator>::iterator::operator--() 
{
    --this->ptr;
    return *this;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::iterator 
Vector<T, allocator>::iterator::operator--(int) 
{
    iterator tmp = *this;
    --this->ptr;
    return tmp;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::reference 
Vector<T, allocator>::iterator::operator*() 
{
    return *this->ptr;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::pointer 
Vector<T, allocator>::iterator::operator->() 
{
    return this->ptr;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::reference 
Vector<T, allocator>::iterator::operator[](size_type pos) const 
{
    return *(this->ptr + pos);
}

template <typename T, typename allocator>
Vector<T, allocator>::const_reverse_iterator::const_reverse_iterator(pointer ptr) : 
    ptr(ptr) 
{}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_reverse_iterator 
Vector<T, allocator>::const_reverse_iterator::operator+(size_type n) const 
{
    return const_reverse_iterator(ptr - n);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_reverse_iterator 
Vector<T, allocator>::const_reverse_iterator::operator-(size_type n) const 
{
    return const_reverse_iterator(ptr + n);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_reverse_iterator& 
Vector<T, allocator>::const_reverse_iterator::operator++() 
{
    --ptr;
    return *this;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_reverse_iterator 
Vector<T, allocator>::const_reverse_iterator::operator++(int) 
{
    const_reverse_iterator tmp = *this;
    --ptr;
    return tmp;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_reverse_iterator& 
Vector<T, allocator>::const_reverse_iterator::operator--() 
{
    ++ptr;
    return *this;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_reverse_iterator 
Vector<T, allocator>::const_reverse_iterator::operator--(int) 
{
    const_reverse_iterator tmp = *this;
    ++ptr;
    return tmp;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_reference 
Vector<T, allocator>::const_reverse_iterator::operator*() const 
{
    return *ptr;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_pointer 
Vector<T, allocator>::const_reverse_iterator::operator->() const 
{
    return ptr;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::const_reference 
Vector<T, allocator>::const_reverse_iterator::operator[](size_type pos) const 
{
    return *(ptr - pos);
}

template <typename T, typename allocator>
bool Vector<T, allocator>::const_reverse_iterator::operator==(const const_reverse_iterator& other) const 
{
    return ptr == other.ptr;
}

template <typename T, typename allocator>
bool Vector<T, allocator>::const_reverse_iterator::operator!=(const const_reverse_iterator& other) const 
{
    return ptr != other.ptr;
}

template <typename T, typename allocator>
bool Vector<T, allocator>::const_reverse_iterator::operator<(const const_reverse_iterator& other) const 
{
    return ptr > other.ptr;
}

template <typename T, typename allocator>
bool Vector<T, allocator>::const_reverse_iterator::operator<=(const const_reverse_iterator& other) const 
{
    return ptr >= other.ptr;
}

// const_reverse_iterator greater than operator>
template <typename T, typename allocator>
bool Vector<T, allocator>::const_reverse_iterator::operator>(const const_reverse_iterator& other) const 
{
    return ptr < other.ptr;
}

template <typename T, typename allocator>
bool Vector<T, allocator>::const_reverse_iterator::operator>=(const const_reverse_iterator& other) const 
{
    return ptr <= other.ptr;
}

template <typename T, typename allocator>
Vector<T, allocator>::reverse_iterator::reverse_iterator(pointer ptr) : 
    const_reverse_iterator(ptr) 
{}

template <typename T, typename allocator>
typename Vector<T, allocator>::reverse_iterator 
Vector<T, allocator>::reverse_iterator::operator+(size_type n) const 
{
    return reverse_iterator(this->ptr - n);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::reverse_iterator 
Vector<T, allocator>::reverse_iterator::operator-(size_type n) const 
{
    return reverse_iterator(this->ptr + n);
}

template <typename T, typename allocator>
typename Vector<T, allocator>::reverse_iterator& 
Vector<T, allocator>::reverse_iterator::operator++() 
{
    --this->ptr;
    return *this;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::reverse_iterator 
Vector<T, allocator>::reverse_iterator::operator++(int) 
{
    reverse_iterator tmp = *this;
    --this->ptr;
    return tmp;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::reverse_iterator& 
Vector<T, allocator>::reverse_iterator::operator--() 
{
    ++this->ptr;
    return *this;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::reverse_iterator 
Vector<T, allocator>::reverse_iterator::operator--(int) 
{
    reverse_iterator tmp = *this;
    ++this->ptr;
    return tmp;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::reference 
Vector<T, allocator>::reverse_iterator::operator*() 
{
    return *this->ptr;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::pointer 
Vector<T, allocator>::reverse_iterator::operator->() 
{
    return this->ptr;
}

template <typename T, typename allocator>
typename Vector<T, allocator>::reference 
Vector<T, allocator>::reverse_iterator::operator[](size_type pos) const 
{
    return *(this->ptr - pos);
}




}

#endif

