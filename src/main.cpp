#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "domain.h"

int main() {
    QueryBuilder builder{};
    try {
        std::cout << builder.getRawData() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}