
#pragma once

#ifndef CPPHTTPLIB_OPENSSL_SUPPORT
#define CPPHTTPLIB_OPENSSL_SUPPORT
#endif

#include <string>

#include "domain.h"

namespace maps {

    class RawDataLoader {
    public:
        std::string GetRawData() const;

    private:
        // Google Maps
        const std::string gmap_base_url_ = MapProviderUrls::GoogleMap.base_url;
        const std::string gmap_query_ = MapProviderUrls::GoogleMap.query;
    };
}