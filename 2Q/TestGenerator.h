#pragma once

#include <iostream>
#include <vector>
#include <random>
#include "2Q.hpp"

enum {MAX_NUM_REQUETS = 100, NUM_PAGES = 1500, DISTANCE_BETWEEN_PEAKS = 700};

class RandomGenerator_t {
public:
    RandomGenerator_t();
    void print ();
    std::vector<size_t>& requests() {return requests_;}
private:
    std::vector<size_t> requests_;
    void GenerateArray();
};

void TestRandom(size_t numTests);

