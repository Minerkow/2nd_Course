#include <iostream>
#include "Matrix.hpp"
#include "Graph.hpp"

int main() {
    std::string str = "1 -- 2, 0;\n"
                      "2 -- 3, 1; 2V\n"
                      "3 -- 1, 0;\n"
                      "3 -- 4, 0;\n"
                      "2 -- 4, 0;";
    std::stringstream is{str};
    grph::RTGraph_t rtGraph{is};
    mtrx::Matrix_t<int> res = rtGraph.Find_Cycles();
    std::cout << res << std::endl;
//
//    std::vector<double> res = rtGraph.Calculate_Potential();
//    for (auto& it : res) {
//        std::cout << it << " ";
//    }

    return 0;
}
