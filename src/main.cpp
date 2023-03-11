#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "domain.h"
#include "map_version_info.h"

int main() {
    QueryBuilder_ builder;
    // std::cout << builder.getRawData() << std::endl;
    const std::string data = builder.getRawData();
    Parser_ parser{};
    std::string_view line = parser.FindVersionInfoLine(data);
    auto res = parser.GetVersionInfo(line);
    auto version = parser.GetVersion(line);
}