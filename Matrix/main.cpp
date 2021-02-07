#include <iostream>
#include "Matrix.hpp"
#include "Graph.hpp"

int main() {
    try {
        grph::RTGraph_t gr(std::cin);
        std::vector<double> res = gr.Calculate_Potential();
        for (auto& it : res) {
            std:: cout << it << " ";
        }
    } catch (std::exception) {
        std::cerr << "Incorrect input";
    }

    return 0;
}
