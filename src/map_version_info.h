#pragma once

#include <map>
#include <string>
#include <string_view>
#include <vector>

#include "raw_data_loader.h"

namespace maps {

    std::vector<std::string_view> SplitIntoWords(std::string_view str, char delimiter = ' ');

    class Parser_ {
    public:
        /// Find version info string in raw data
        /// Returns version info string, example string:
        /// "//khms0.google.com/kh/v\u003d943","//khms1.google.com/kh/v\u003d943","//khms2.google.com/kh/v\u003d943","//khms3.google.com/kh/v\u003d943"
        /// Returns version info string
        std::string_view FindVersionInfoLine(std::string_view text) const;

        std::map<std::string, std::string> GetVersionInfo(std::string_view text) const;
        std::string GetVersion(std::map<std::string, std::string> info) const;
        std::string GetVersion(std::string_view text) const;

    private:
        std::string_view FindGoogleVersionInfoLine_(std::string_view text) const;
        std::map<std::string, std::string> GetGoogleVersionInfo_(std::string_view text) const;
    };

    class MapVersionInfo {
    public:
        MapVersionInfo() = default;
        std::string GetMapVersion() const;

    private:
        Parser_ parser_;
        RawDataLoader loader_;
    };

}