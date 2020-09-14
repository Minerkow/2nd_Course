#include "TestGenerator.h"

RandomGenerator_t::RandomGenerator_t() {
    requests_ = std::vector<size_t>(MAX_NUM_REQUETS);
    requests_.shrink_to_fit();
    GenerateArray();
}

void RandomGenerator_t::GenerateArray() {
    std::random_device rd{};
    std::mt19937 gen{rd()};
    if (DISTANCE_BETWEEN_PEAKS > NUM_PAGES / 4 * 3) {
        std::cerr << "BIG DESTANCE" << std::endl;
        exit(ERROR);
    }
    std::normal_distribution<double> normDistr1(NUM_PAGES / 4, NUM_PAGES / 4),
                                     normDistr2(NUM_PAGES / 4 + DISTANCE_BETWEEN_PEAKS,
                                                NUM_PAGES / 4);
    for (auto& req : requests_) {
        switch (random() % 2) {
            case 0 :
                req = std::abs(lround(normDistr1(gen))) % NUM_PAGES; break;
            case 1:
                req = std::abs(lround(normDistr2(gen))) % NUM_PAGES; break;
        }
    }
}

void RandomGenerator_t::print() {
    for (auto& i : requests_) {
        std::cout << i << " ";
    }
}

void TestRandom(size_t numTests) {
    for (size_t i = 0; i < numTests; ++i) {
        Cache2Q_t<int> cache(CACHE_SIZE);
        LRU_t<int> cacheLRU(CACHE_SIZE);
        RandomGenerator_t rnd;
        cache.load_from_array(rnd.requests());
        cacheLRU.load_from_array(rnd.requests());
        cacheLRU.print_statistic();
        cache.print_statistic();
    }
    std::cerr << "Test 2Q - OK" << std::endl;
}
