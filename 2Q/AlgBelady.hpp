#include <vector>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>

#include "2Q.hpp"

enum {MAX_ID = INTMAX_MAX};

//template <typename T>
class BeladyCache_t {
public:
    using cacheIterator = std::unordered_map<size_t, object_t<int>>::iterator;
    using sortedOffsetIterator = std::map<size_t, cacheIterator>::iterator;

    explicit BeladyCache_t(size_t cacheSize, std::vector<size_t> requests);
    void fill_history(std::vector<size_t>& requests);
    void check(size_t id);
    void add(size_t id);
    cacheIterator find(size_t id) {return cache_.find(id);};
    cacheIterator end() {return cache_.end();};
    void erase_max_offset();
    void update_offset();
    void print_hit() const {std::cout << hit_;};
    void print_data();
    sortedOffsetIterator min_offset_object();
    sortedOffsetIterator max_offset_object();
private:
    std::unordered_map<size_t, std::queue<size_t>> history_;
    std::unordered_map<size_t, object_t<int>> cache_;
    std::map<size_t, cacheIterator> sortedOffsets_;
    size_t hit_;
    size_t capacity_;
    size_t size_;
    size_t numrequests_{};
};

void BeladyCache_t::fill_history(std::vector<size_t> &requests) {
    size_t it = 0;
    for (auto& id : requests) {
        history_[id].push(it);
        it++;
    }
}

void BeladyCache_t::check(size_t id) {
    numrequests_++;
    assert(size_ <= capacity_);

    update_offset();

    if (find(id) != end()) {
        hit_++;
        return;
    }
    if (size_ < capacity_) {
        add(id);
        size_++;
        return;
    }

    if (size_ == capacity_) {
        erase_max_offset();
        add(id);
    }

}

void BeladyCache_t::add(size_t id) {
    cache_.emplace( id, load_by_id<int>(id));
    sortedOffsets_.emplace(history_[id].front(), cache_.find(id));
    history_[id].pop();
}

void BeladyCache_t::erase_max_offset() {
    cacheIterator iter = max_offset_object()->second;
    cache_.erase(iter);
    sortedOffsets_.erase(max_offset_object());
}

BeladyCache_t::BeladyCache_t(size_t cacheSize, std::vector<size_t> requests) {
    fill_history(requests);
    hit_ = 0;
    capacity_ = cacheSize;
    size_ = 0;
}

void BeladyCache_t::print_data() {
    for(auto& it : cache_) {
        std::cout << it.first << " " ;
    }
    std::cout << std::endl;
}

void BeladyCache_t::update_offset() {
    if (size_ == 0) {
        return;
    }
    while (min_offset_object()->first < numrequests_ && min_offset_object() != max_offset_object()) {
        size_t id = min_offset_object()->second->first;
        sortedOffsetIterator it = min_offset_object();
        if (history_[id].empty()) {
            sortedOffsets_.erase(it);
            sortedOffsets_.emplace(MAX_ID, cache_.find(id));
            return;
        }

        size_t offset = history_[id].front();
        history_[id].pop();
        sortedOffsets_[offset] = it->second;
        sortedOffsets_.erase(it);
    }
}

BeladyCache_t::sortedOffsetIterator BeladyCache_t::max_offset_object() {
    return std::prev(sortedOffsets_.end());
}

BeladyCache_t::sortedOffsetIterator BeladyCache_t::min_offset_object() {
    return sortedOffsets_.begin();
}






