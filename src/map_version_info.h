#pragma once

#include <algorithm>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "domain.h"
#include "raw_data_loader.h"

namespace maps {

    inline std::vector<std::string_view> SplitIntoWords(std::string_view str, char delimiter = ' ') {
        if (str.empty()) {
            return {};
        }
        std::vector<std::string_view> result;
        str.remove_prefix(std::min(str.find_first_not_of(delimiter), str.size()));

        do {
            int64_t space = str.find(delimiter, 0);
            result.push_back(space == static_cast<int64_t>(str.npos) ? str.substr(0) : str.substr(0, space));
            str.remove_prefix(std::min(str.find_first_not_of(delimiter, space), str.size()));
        } while (!str.empty());

        return result;
    }

    class Parser_ {
    public:
        /// Find version info string in raw data
        /// Returns version info string, example string:
        /// "//khms0.google.com/kh/v\u003d943","//khms1.google.com/kh/v\u003d943","//khms2.google.com/kh/v\u003d943","//khms3.google.com/kh/v\u003d943"
        /// Returns version info string
        std::string_view FindVersionInfoLine(std::string_view text) const {
            return FindGoogleVersionInfoLine_(text);
        }

        std::map<std::string, std::string> GetVersionInfo(std::string_view text) const {
            return GetGoogleVersionInfo_(text);
        }

        std::string GetVersion(std::map<std::string, std::string> info) const {
            if (info.empty()) {
                return {};
            }

            return info.cbegin()->second;
        }

        std::string GetVersion(std::string_view text) const {
            const auto info = GetVersionInfo(text);
            return GetVersion(info);
        }

    private:
        std::string_view FindGoogleVersionInfoLine_(std::string_view text) const {
            const std::string find_prefix = "\"//khms0.google.com/kh/v"s;
            while ((text.length() > find_prefix.length()) && !text.starts_with(find_prefix)) {
                // const size_t idx = text.find("[");
                text.remove_prefix(text.find("[") + 1);
            }

            if (!text.empty()) {
                // const size_t idx = text.find("]");
                text.remove_suffix(text.size() - text.find("]"));
            }

            return text;
        }

        std::map<std::string, std::string> GetGoogleVersionInfo_(std::string_view text) const {
            auto lines = SplitIntoWords(text, ',');
            std::map<std::string, std::string> result;
            std::for_each(lines.begin(), lines.end(), [&result](std::string_view str) {
                str.remove_prefix(std::min(str.find("\"") + 1, str.size()));
                str = str.substr(0, std::min(str.rfind("\""), str.size()));
                const size_t end_key_idx = std::min(str.rfind("\\"), str.size());

                const auto val = str.substr(end_key_idx + std::min(6UL, str.length()));
                const auto key = str.substr(0, end_key_idx);

                result.emplace(key, val);
            });

            return result;
        }
    };

    class MapVersionInfo {
    public:
        MapVersionInfo() = default;
        std::string GetMapVersion() {
            const auto raw_data = loader_.GetRawData();
            const auto data_line = parser_.FindVersionInfoLine(raw_data);
            if (raw_data.empty() || data_line.empty()) {
                std::cerr << "Empty result" << std::endl;
                return {};
            }
            return parser_.GetVersion(data_line);
        }

    private:
        const Parser_ parser_;
        const RawDataLoader loader_;
    };

}