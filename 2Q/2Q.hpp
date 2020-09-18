#pragma once

#include <iostream>
#include <unordered_map>
#include <list>
#include <cassert>
#include "TestGenerator.h"

enum {  CACHE_SIZE = 100, RECOMENDED_SIZE = 10, MIN_2QCACHE_SIZE = 3,
        ERROR = 1, PART_IN = 2, PART_MAIN = 2, PARTS = 3 };

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
    explicit HashList_t(size_t size = 0) : list_(0), hashT_(0), capacity_(size){};
    listIterator add(size_t id);
    void pop_back();
    void move_in_other(HashList_t& other, listIterator elem);
    listIterator find (size_t id);
    const size_t capacity() const {return capacity_;};
    const size_t size() const {return list_.size();}
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
    size_t size() const {return in_.size() + out_.size() + main_.size();};
private:
    HashList_t<T> in_;
    HashList_t<T> out_;
    HashList_t<T> main_;
    size_t hit_{};
    size_t numRequest_{};
};

template<typename T>
class LRU_t {
public:
    explicit LRU_t(size_t size) : cache(size), hit_(0), numrequests_(0){}
    void load_from_array(std::vector<size_t>& vec);
    void print_statistic();
    void check(size_t id);
    void print_hit() {std::cout<< hit_ << std::endl;};
private:
    HashList_t<T> cache;
    size_t hit_;
    size_t numrequests_;
};

template<typename T>
void LRU_t<T>::check(size_t id) {
    numrequests_++;
    if (cache.find(id) != cache.end()) {
        hit_++;
        cache.move_in_other(cache, cache.find(id));
        return;
    }
    cache.add(id);
}

template<typename T>
void LRU_t<T>::load_from_array(std::vector<size_t> &vec) {
    for (auto& req : vec) {
        check(req);
    }
}

template<typename T>
void LRU_t<T>::print_statistic() {
    std::cerr << "LRU: [ Hits: " << hit_ << ", "
              << double (hit_) / double (numrequests_) << " ]" << std::endl;
}


template<typename T>
void HashList_t<T>::pop_back(){
    hashT_.erase(list_.back().id);
    list_.pop_back();
}



template<typename T>
void HashList_t<T>::move_in_other(HashList_t &other, listIterator elem) {
    size_t id = elem->id;
    other.list_.splice(other.list_.begin(), list_, elem);
    if (other.size() > other.capacity_)
        other.pop_back();
    hashT_.erase(id);
    other.hashT_.emplace(id, other.list_.begin());
}

template<typename T>
typename HashList_t<T>::listIterator HashList_t<T>::find (size_t id) {
    auto itOnObject = hashT_.find(id);
    if (itOnObject == hashT_.end()) {
        return list_.end();
    } else {
        return itOnObject->second;
    }
}

template<typename T>
typename HashList_t<T>::listIterator HashList_t<T>::add(size_t id) {

    object_t<T> obj = load_by_id<T>(id);
    list_.push_front(obj);
    hashT_.emplace(id, list_.begin());

    if (list_.size() > capacity_) {
        hashT_.erase(list_.back().id);
        list_.pop_back();
    }
    return list_.begin();
}

template<typename T>
void HashList_t<T>::print() {
    std::cout << "[";
    for (auto& i : list_) {
        std::cout << i.id << " ";
    }
    std::cout << "]\n";
}

template<typename T>
void HashList_t<T>::clear() {
    capacity_ = 0;
    hashT_.clear();
    list_.clear();
}

template<typename T>
HashList_t<T>::~HashList_t() {
    capacity_ = 0;
    hashT_.clear();
    list_.clear();
}

template<typename T>
typename Cache2Q_t<T>::listIterator Cache2Q_t<T>::check(size_t id) {
    numRequest_++;
    listIterator ptrOnObject = in_.find(id);
    if (ptrOnObject != in_.end()) {
        hit_++;
        in_.move_in_other(in_, ptrOnObject);
        return ptrOnObject;
    }
    ptrOnObject = out_.find(id);
    if (ptrOnObject != out_.end()) {
        hit_++;
        out_.move_in_other(main_, ptrOnObject);
        return ptrOnObject;
    }
    ptrOnObject = main_.find(id);
    if (ptrOnObject != main_.end()) {
        hit_++;
        main_.move_in_other(main_, ptrOnObject);
        return ptrOnObject;
    }
    if (in_.capacity() == in_.size()) {
        in_.move_in_other(out_, prev(in_.end()));
    }
    listIterator it = in_.add(id);
    return it;
}

template<typename T>
void Cache2Q_t<T>::print_hit() {
    std::cout << hit_ << std::endl;
}

template<typename T>
void Cache2Q_t<T>::print_data() {
    std::cout << "in: ";
    in_.print();
    std::cout << "out: ";
    out_.print();
    std::cout << "main: ";
    main_.print();
}
template<typename T>
void Cache2Q_t<T>::load_from_array(std::vector<size_t>& vec) {
    for (auto& req : vec) {
        check(req);
    }
}

template<typename T>
void Cache2Q_t<T>::print_statistic() {
    std::cerr << "2Q: [ Hits: " << hit_ << ", "
              << double (hit_) / double (numRequest_) << " ]" << std::endl;
}

template<typename T>
void Cache2Q_t<T>::clear() {
    in_.clear();
    out_.clear();
    main_.clear();
    numRequest_ = 0;
    hit_ = 0;
}

template<typename T>
Cache2Q_t<T>::Cache2Q_t(size_t size) {
    if (size < 0) {
        std::cerr << "SMALL SIZE ERROR" << std::endl;
        exit(ERROR);
    }
    if(size >= RECOMENDED_SIZE) {
        in_ = HashList_t<T>(size / RECOMENDED_SIZE * PART_IN);
        main_ = HashList_t<T>(size / RECOMENDED_SIZE * PART_MAIN);
        out_ = HashList_t<T>(size - size / RECOMENDED_SIZE * (PART_MAIN + PART_IN));
    } else {
        in_ = HashList_t<T>(size / PARTS);
        main_ = HashList_t<T>(size / PARTS);
        out_ = HashList_t<T>(size - size / PARTS * 2);
    }
    hit_ = 0;
    numRequest_ = 0;
}

template <typename T>
object_t<T> load_by_id(size_t id) {
    object_t<T> obj;
    obj.id = id;
    return obj;
}








