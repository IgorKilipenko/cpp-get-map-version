#pragma once

#include <optional>
#include <string>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../libs/httplib.h"

using namespace std::string_literals;

struct MapProviderInfo {
    std::string base_url;
    std::string query;
    std::string version;
};

struct MapProviderUrls {
    inline static const MapProviderInfo GoogleMap{
        .base_url = "https://www.google.com"s, .query = "/maps/@38.7848036,-97.6093175,57m/data=!3m1!1e3"s, .version = ""s};
};

class QueryBuilder_ {
public:
    std::string getRawData() const;

private:
    // Google Maps
    inline static const std::string gmap_base_url_ = MapProviderUrls::GoogleMap.base_url;
    inline static const std::string gmap_query_ = MapProviderUrls::GoogleMap.query;
};

inline std::string QueryBuilder_::getRawData() const {
    using namespace httplib;

    httplib::Client cli(gmap_base_url_);

    std::optional<httplib::Result> res;
    try {
        res = cli.Get(gmap_query_);

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