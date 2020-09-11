
#include "2Q.h"

template<typename T>
void HashList_t<T>::move_in_other(HashList_t &other, listIterator elem) {
    size_t id = elem->id;
    other.list_.splice(other.list_.begin(), list_, elem);
    hashT_.erase(id);
    other.hashT_.emplace(id, other.list_.begin());
}

template<typename T>
typename HashList_t<T>::listIterator HashList_t<T>::find(size_t id) {
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
    if (list_.size() <= size_)
        return list_.begin();
    hashT_.erase(list_.back().id);
    list_.pop_back();
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
    size_ = 0;
    hashT_.clear();
    list_.clear();
}

template<typename T>
typename Cache2Q_t<T>::listIterator Cache2Q_t<T>::check(size_t id) {
    numRequest_++;
    listIterator ptrOnObject = in_.find(id);
    if (ptrOnObject != in_.end()) {
        in_.move_in_other(out_, ptrOnObject);
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
        return ptrOnObject;
    }
    in_.move_in_other(out_, prev(in_.end()));
    listIterator it = in_.add(id);
    return it;
}

template<typename T>
void Cache2Q_t<T>::print_hit() {
    std::cout << "Hits:" << hit_;
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
    std::cerr << "[ Hits: " << hit_ << ", "
              << double(hit_) / double (numRequest_) << " ]\n";
}

template<typename T>
void Cache2Q_t<T>::clear() {
    in_.clear();
    out_.clear();
    main_.clear();
    numRequest_ = 0;
    hit_ = 0;
}

template <typename T>
object_t<T> load_by_id(size_t id) {
    object_t<T> obj;
    obj.id = id;
    return obj;
}





