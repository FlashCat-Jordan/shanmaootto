#pragma once

#include <string>

// Standalone-build compatibility for the OTA URL validator used by ota.cc.
// The upstream project obtains this small declaration from its build
// environment; keeping it here makes this extracted repository self-contained.
namespace wifi_config {

inline bool IsValidOtaUrl(const std::string& url) {
    if (url.empty()) {
        return false;
    }
    if (url.rfind("https://", 0) != 0 && url.rfind("http://", 0) != 0) {
        return false;
    }
    const auto scheme_end = url.find("://");
    return scheme_end != std::string::npos && url.size() > scheme_end + 3;
}

}  // namespace wifi_config
