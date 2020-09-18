#include "AlgBelady.hpp"

template <typename T>
void RunTest(T cache, size_t numKeys);

int main() {
    size_t cacheSize, numKeys;
    std::cin >> cacheSize >> numKeys;
    if (cacheSize > MIN_2QCACHE_SIZE) {
        Cache2Q_t<int> cache2Q(cacheSize);
        RunTest(cache2Q, numKeys);
    } else {
        LRU_t<int> cacheLRU(cacheSize);
        RunTest(cacheLRU, numKeys);
    }
    return 0;
}






template <typename T>
void RunTest(T cache, size_t numKeys) {
    for (size_t i = 0; i < numKeys; ++i) {
        size_t id = 0;
        std::cin >> id;
        cache.check(id);
    }
    cache.print_hit();
}
