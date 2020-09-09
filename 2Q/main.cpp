#include <iostream>
#include "2Q.h"

int main() {
    size_t s = 10;
    Cache2Q_t<int> in(10);
    for (size_t i = 0; i < 10; ++i) {
        in.check(i);
    }
    in.print_hit();
    std::cout << "\n";
    in.print_data();
    return 0;
}
