#pragma once

#include <iostream>
#include <vector>
#include <random>
#include "2Q.h"

enum {MAX_NUM_REQUETS = 100, NUM_PAGES = 200};

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

