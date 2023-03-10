#pragma once

#include <optional>
#include <string>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../libs/httplib.h"

using namespace std::string_literals;

class QueryBuilder {
public:
    std::string getRawData() const;

private:
    const std::string gmap_req_url_ = "https://www.google.com"s;
};

inline std::string QueryBuilder::getRawData() const {
    using namespace httplib;

    httplib::Client cli(gmap_req_url_);

    std::optional<httplib::Result> res;
    try {
        res = cli.Get("/maps/@38.7848036,-97.6093175,57m/data=!3m1!1e3");

    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        res = std::nullopt;
    }

    if (res.has_value()) {
        try {
            auto resp = res->value();
            std::cout << resp.status << std::endl;
            return res->value().body;

        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    return ""s;
}