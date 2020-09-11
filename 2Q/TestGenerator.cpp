#include "TestGenerator.h"

RandomGenerator_t::RandomGenerator_t() {
    requests_ = std::vector<size_t>(MAX_NUM_REQUETS);
    requests_.shrink_to_fit();
    GenerateArray();
}

void RandomGenerator_t::GenerateArray() {
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<double> normDistr(NUM_PAGES / 2, NUM_PAGES / 4);
    for (auto& req : requests_) {
        req = std::abs(lround(normDistr(gen))) % NUM_PAGES;
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
        RandomGenerator_t rnd;
        cache.load_from_array(rnd.requests());
        cache.print_statistic();
    }
    std::cerr << "Test 2Q - OK" << std::endl;
}
