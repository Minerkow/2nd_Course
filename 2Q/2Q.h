#pragma once

#include <iostream>
#include <unordered_map>
#include <list>
#include <assert.h>
#include "TestGenerator.h"

enum {CACHE_SIZE = 100, ERROR = 1};

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
    explicit HashList_t(size_t size) : list_(0), hashT_(0), capacity_(size){};
    HashList_t(): list_(0), hashT_(0), capacity_(0){};
    listIterator add(size_t id);
    void move_in_other(HashList_t& other, listIterator elem);
    listIterator find(size_t id);
    size_t capacity() {return capacity_;};
    size_t size() {return list_.size();}
    listIterator end() {return list_.end();};
    void print();
    void clear();
    ~HashList_t();
private:
    size_t capacity_;
    std::unordered_map<size_t, listIterator> hashT_;
    std::list<object_t<T>> list_;
};

template <typename T>
class Cache2Q_t {
public:
    using listIterator = typename std::list<object_t<T>>::iterator;
    explicit Cache2Q_t(size_t size);
    listIterator check(size_t id);
    void print_hit();
    void print_data();
    void clear();
    void load_from_array(std::vector<size_t>& vec);
    void print_statistic();
private:
    HashList_t<T> in_;
    HashList_t<T> out_;
    HashList_t<T> main_;
    size_t hit_{};
    size_t numRequest_{};
};



#include "2Q.inl"
