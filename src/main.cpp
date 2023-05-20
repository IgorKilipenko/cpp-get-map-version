#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "domain.h"
#include "map_version_info.h"

int main() {
    maps::MapVersionInfo version_getter;
    const auto version = version_getter.GetMapVersion();

    std::cout << std::endl << "Google Maps version: " << version << std::endl << std::endl;
}