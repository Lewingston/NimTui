
#include "Unicode.h"

#include "wtswidth.h"

#include <utility>

using namespace TUI;


Unicode::Info Unicode::getInfo(const std::string& str) noexcept {

    return getInfo(str.c_str(), str.length());
}


Unicode::Info Unicode::getInfo(const std::string& str, std::size_t offset) noexcept {

    const s32 remainingLength = static_cast<s32>(str.length()) - static_cast<s32>(offset);

    if (!std::in_range<std::size_t>(remainingLength))
        return Info();

    return getInfo(str.c_str() + offset, static_cast<std::size_t>(remainingLength));
}


Unicode::Info Unicode::getInfo(const char* str, std::size_t len) noexcept {

    s32 width = 0;
    const s32 byteCount = wts8clusterlen(str, len, &width);

    if (!std::in_range<u8>(width) || !std::in_range<u8>(byteCount)) {

        // Possible encoding error
        return Info();

    } else {

        return Info {
            .byteCount = static_cast<u8>(byteCount),
            .width     = static_cast<u8>(width)
        };
    }
}
