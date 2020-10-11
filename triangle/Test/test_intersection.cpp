#include <gtest/gtest.h>
#include "../Triangle.h"
#include "../IntersectionTriangles.h"
#include "test_generator.h"

TEST(TrianglesGenerator, Constructor) {
    trgtest::TrianglesGenerator_t test;
    std::cout << test;
}