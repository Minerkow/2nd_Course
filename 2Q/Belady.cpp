#include "AlgBelady.hpp"

int main() {
    size_t cacheSize, numKeys;
    std::cin >> cacheSize >> numKeys;
    std::vector<size_t> reqs;
    for (size_t i = 0; i < numKeys; ++i) {
        size_t id = 0;
        std::cin >> id;
        reqs.push_back(id);
    }
    BeladyCache_t cache(cacheSize, reqs);
    for (auto &id : reqs) {
        cache.check(id);
    }
    cache.print_hit();
    return 0;
}