#ifndef __VECTOR__H__
#define __VECTOR__H__

#include <iostream>
#include <memory>

namespace g3
{
    
template <typename T, typename allocator = std::allocator<T>>
class Vector
{
public:
    using value_type = T;
    using allocatortype = allocator;
    using size_type = std::size_t;    
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

public:
    class const_iterator;
    class iterator;
    class const_reverse_iterator;
    class reverse_iterator;

public:

    Vector(); 
    Vector(const Vector& rhv); 
    Vector(Vector&& rhv);
    Vector(std::initializer_list<value_type> init);
    Vector(size_type size, const_reference val = value_type{});
    template <typename InputIt>
    Vector(InputIt first, InputIt last);
    ~Vector();

public:

    const Vector& operator=(const Vector& rhv);
    const Vector& operator=(Vector&& rhv);

    allocatortype get_allocator();

public:
    reference at(size_type pos);
    const_reference at(size_type pos) const;

    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;

    reference front();
    const_reference front() const;

    reference back();
    const_reference back() const;

public:
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    
    iterator rbegin();
    const_iterator rbegin() const;
    const_iterator crbegin() const;
    
    iterator rend();
    const_iterator rend() const;
    const_iterator crend() const;
    
public:
    bool empty() const;
    size_type size() const;
    size_type capacity() const;

    void reserve(size_type new_cap);

public:
    void clear() noexcept;

    iterator insert(const_iterator pos, const_reference val);
    iterator insert(const_iterator pos, size_type count, const_reference val);
    iterator insert(const_iterator pos, std::initializer_list<value_type> init);
    template <typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last);

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);

    void push_back(const_reference val);
    void pop_back();

    void resize(size_type new_size, const_reference val = value_type{});

public:
    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;
    bool operator<(const Vector& other) const;
    bool operator<=(const Vector& other) const;
    bool operator>(const Vector& other) const;
    bool operator>=(const Vector& other) const;

private:
    int compare(const Vector& other) const;
    
private:
    allocatortype alloc_;
    size_type size_;
    size_type capacity_;
    pointer arr_;
};

template <typename T, typename allocator>
class Vector<T, allocator>::const_iterator
{
    friend class Vector<T, allocator>;
protected:
    pointer ptr;
private:
    const_iterator(pointer ptr);
public:
    const_iterator() = default;
    const_iterator(const const_iterator&) = default;      
    const_iterator(const_iterator&&) = default;

    const_iterator& operator=(const const_iterator&) = default;      
    const_iterator& operator=(const_iterator&&) = default;

    const_iterator operator+(size_type n) const;      
    const_iterator operator-(size_type n) const;

    const_iterator& operator++();
    const_iterator operator++(int);
    const_iterator& operator--();
    const_iterator operator--(int);

    const_reference operator*() const;
    const_pointer operator->() const;

    const_reference operator[](size_type pos) const;

    bool operator==(const const_iterator& other) const;      
    bool operator!=(const const_iterator& other) const;      
    bool operator<(const const_iterator& other) const;      
    bool operator<=(const const_iterator& other) const;      
    bool operator>(const const_iterator& other) const;      
    bool operator>=(const const_iterator& other) const;      
};

template <typename T, typename allocator>
class Vector<T, allocator>::iterator : Vector<T, allocator>::const_iterator
{
    friend class Vector<T, allocator>;
private:
    iterator(pointer ptr);
public:
    iterator() = default;
    iterator(const iterator&) = default;      
    iterator(iterator&&) = default;

    iterator& operator=(const iterator&) = default;      
    iterator& operator=(iterator&&) = default;

    iterator operator+(size_type n) const;      
    iterator operator-(size_type n) const;

    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);

    reference operator*();
    pointer operator->();

    reference operator[](size_type pos) const;
};


template <typename T, typename allocator>
class Vector<T, allocator>::const_reverse_iterator
{
    friend class Vector<T, allocator>;
protected:
    pointer ptr;
private:
    const_reverse_iterator(pointer ptr);
public:
    const_reverse_iterator() = default;
    const_reverse_iterator(const const_reverse_iterator&) = default;      
    const_reverse_iterator(const_reverse_iterator&&) = default;

    const_reverse_iterator& operator=(const const_reverse_iterator&) = default;      
    const_reverse_iterator& operator=(const_reverse_iterator&&) = default;

    const_reverse_iterator operator+(size_type n) const;      
    const_reverse_iterator operator-(size_type n) const;

    const_reverse_iterator& operator++();
    const_reverse_iterator operator++(int);
    const_reverse_iterator& operator--();
    const_reverse_iterator operator--(int);

    const_reference operator*() const;
    const_pointer operator->() const;

    const_reference operator[](size_type pos) const;

    bool operator==(const const_reverse_iterator& other) const;      
    bool operator!=(const const_reverse_iterator& other) const;      
    bool operator<(const const_reverse_iterator& other) const;      
    bool operator<=(const const_reverse_iterator& other) const;      
    bool operator>(const const_reverse_iterator& other) const;      
    bool operator>=(const const_reverse_iterator& other) const;      
};

template <typename T, typename allocator>
class Vector<T, allocator>::reverse_iterator : Vector<T, allocator>::const_reverse_iterator
{
    friend class Vector<T, allocator>;
private:
    reverse_iterator(pointer ptr);
public:
    reverse_iterator() = default;
    reverse_iterator(const reverse_iterator&) = default;      
    reverse_iterator(reverse_iterator&&) = default;

    reverse_iterator& operator=(const reverse_iterator&) = default;      
    reverse_iterator& operator=(reverse_iterator&&) = default;

    reverse_iterator operator+(size_type n) const;      
    reverse_iterator operator-(size_type n) const;

    reverse_iterator& operator++();
    reverse_iterator operator++(int);
    reverse_iterator& operator--();
    reverse_iterator operator--(int);

    reference operator*();
    pointer operator->();

    reference operator[](size_type pos) const;
};

}

#include "vector.hpp"

#endif