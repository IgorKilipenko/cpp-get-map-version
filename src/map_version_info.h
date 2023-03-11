#pragma once

#include <algorithm>
#include <cstddef>
#include <ctime>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>

#include "domain.h"

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

    std::map<std::string, std::string> GetVersionInfo(std::string_view text) const {
        auto lines = SplitIntoWords(text, ',');
        std::map<std::string, std::string> result;
        std::for_each(lines.begin(), lines.end(), [&result](std::string_view str) {
            str.remove_prefix(std::min(str.find("\"") + 1, str.size()));
            str = str.substr(0, std::min(str.rfind("\""), str.size()));
            const size_t end_key_idx = std::min(str.rfind("\\"),str.size());
            
            const auto val = str.substr(end_key_idx + std::min(6UL,str.length()));
            const auto key = str.substr(0, end_key_idx);

            result.emplace(key, val);
        });

        return result;
    }

    std::string GetVersion(std::string_view text) {
        const auto info = GetVersionInfo(text);
        if (info.empty()) {
            return ""s;
        }

        std::stringstream ss;
        ss << info.cbegin()->second;
        return ss.str();
    }

    std::string GetVersion(std::map<std::string, std::string> info);
};

class MapVersionInfo {};