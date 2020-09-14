#include "2Q.hpp"

int main() {
    size_t cacheSize, numKeys;
    std::cin >> cacheSize >> numKeys;
    Cache2Q_t<int> cache2Q(cacheSize);
    for (size_t i = 0; i < numKeys; ++i) {
        size_t id = 0;
        std::cin >> id;
        cache2Q.check(id);
    }
    cache2Q.print_hit();
    return 0;
}
