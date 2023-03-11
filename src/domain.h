#pragma once

#include <string>

namespace maps {
    using namespace std::string_literals;

    enum class MapProviders { GOOGLE, YANDEX };

    struct MapProviderInfo {
        std::string base_url;
        std::string query;
        std::string version;
    };

    struct MapProviderUrls {
        inline static const MapProviderInfo GoogleMap{
            .base_url = "https://www.google.com"s, .query = "/maps/@38.7848036,-97.6093175,57m/data=!3m1!1e3"s, .version = ""s};
    };
}