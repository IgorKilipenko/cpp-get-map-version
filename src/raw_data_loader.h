
#pragma once

#ifndef CPPHTTPLIB_OPENSSL_SUPPORT
#define CPPHTTPLIB_OPENSSL_SUPPORT
#endif

#include <iostream>
#include <optional>
#include <string>

#include "httplib.h"
#include "detail/test_framework.h"
#include "domain.h"

namespace maps {

    class RawDataLoader {
    public:
        std::string GetRawData() const;

    private:
        // Google Maps
        inline static const std::string gmap_base_url_ = MapProviderUrls::GoogleMap.base_url;
        inline static const std::string gmap_query_ = MapProviderUrls::GoogleMap.query;
    };

    inline std::string RawDataLoader::GetRawData() const {
        std::string result;
        httplib::Client cli(gmap_base_url_);
        std::optional<httplib::Result> response;

        try {
            response = cli.Get(gmap_query_);

        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            response = std::nullopt;
        }

        if (response.has_value()) {
            try {
                auto resp = response->value();
                if (resp.status != 200) {
                    std::cerr << "Error data loading.\nCode: " << resp.status << std::endl;
                    return result;
                }

                result = response->value().body;

            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        }

        return result;
    }
}