
#include "raw_data_loader.h"

#include <optional>

namespace maps /* RawDataLoader implementation */ {
    std::string RawDataLoader::GetRawData() const {
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