#include <iostream>
#include "Matrix.hpp"
#include "Graph.hpp"

int main() {
    try {
        grph::RTGraph_t gr(std::cin);
        gr.Calculate_Potential();
    } catch (std::exception) {
        std::cerr << "Incorrect input";
    }

    return 0;
}
