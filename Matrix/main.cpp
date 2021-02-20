#include <iostream>
#include "Matrix.hpp"
#include "Graph.hpp"

int main() {
    std::string str = "1 -- 2, 0;\n"
                      "2 -- 3, 1; 2V\n"
                      "3 -- 1, 0;";
    std::stringstream is{str};
    grph::RTGraph_t rtGraph{is};
    rtGraph.Find_Cycles();
//
//    std::vector<double> res = rtGraph.Calculate_Potential();
//    for (auto& it : res) {
//        std::cout << it << " ";
//    }

    return 0;
}
