#pragma once

#include <string>

using namespace std::string_literals;

class QueryBuilder {
public:
    std::string getRawData() const;

private:
    const std::string gmap_req_url = "https://www.google.com/maps/@38.7848036,-97.6093175,57m/data=!3m1!1e3"s;
};

inline std::string QueryBuilder::getRawData() const {
    return "empty"s;
}