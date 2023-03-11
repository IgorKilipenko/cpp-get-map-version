#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "domain.h"
#include "map_version_info.h"


int main() {
    // maps::RawDataLoader loader;
    // const std::string data = loader.GetRawData();
    // maps::Parser_ parser{};
    // std::string_view line = parser.FindVersionInfoLine(data);
    // auto version = parser.GetVersion(line);

    maps::MapVersionInfo version_getter;
    const auto version = version_getter.GetMapVersion();

    std::cout << std::endl <<"Google Maps version: " << version << std::endl << std::endl;
}