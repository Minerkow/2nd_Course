#pragma once

#include <iostream>
#include <unordered_map>
#include <list>


template <typename T>
struct object_t {
    size_t id;
    T data_;
};

template <typename T>
object_t<T> load_by_id(size_t id);

template <typename T>
class HashList_t {
public:
    using listIterator = typename std::list<object_t<T>>::iterator;
    explicit HashList_t(size_t size) : list_(size), hashT_(size), size_(size){};
    listIterator add(size_t id);
    void move_in_other(HashList_t& other, listIterator elem);
    listIterator find(size_t id);
    listIterator end() {return list_.end();};
    void print();
private:
    size_t size_;
    std::unordered_map<size_t, listIterator> hashT_;
    std::list<object_t<T>> list_;
};

template <typename T>
class Cache2Q_t {
public:
    using listIterator = typename std::list<object_t<T>>::iterator;
    explicit Cache2Q_t(size_t size) : main_(size / 10 * 2), in_(size / 10 * 2),
                                      out_(size - size / 10 * 4), hit_(0),
                                      numRequest_(0) {};
    listIterator check(size_t id);
    void print_hit();
    void print_data();
private:
    HashList_t<T> in_;
    HashList_t<T> out_;
    HashList_t<T> main_;
    size_t hit_;
    size_t numRequest_;
};

#include "2Q.inl"
