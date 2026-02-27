
#include "ConsoleString.h"
#include "Common/Utf8Char.h"

#include "wtswidth.h"

#include <optional>

using namespace TUI;


std::string ConsoleString::getSubstring(const std::string& str,
                                        std::size_t pos,
                                        std::size_t count) {

    /*
    const std::size_t startIndex = getByteCountForConsoleSize(str, pos);
    const std::size_t endIndex   = getByteCountForConsoleSize(str, pos + count);

    return str.substr(startIndex, endIndex - startIndex);
    */

    std::string result;

    std::size_t length   = 0;
    u8 lastCharSize = 0;

    // Iterate over string untill we reach start position
    std::size_t startPos = 0;
    while (length < pos) {

        if (startPos >= str.length())
            break;

        lastCharSize = Utf8Char::getByteCount(static_cast<u8>(str.at(startPos)));
        length += static_cast<std::size_t>(wts8width(str.c_str() + startPos, lastCharSize));
        startPos += lastCharSize;
    }

    // If the start position is in the middle of a double width character,
    // substitue with a white space
    if (length > pos) {
        result += " ";
    }

    // Iterate over string untill we reach end position
    std::size_t endPos = startPos;
    while (length < pos + count) {

        if (endPos >= str.length())
            break;

        lastCharSize = Utf8Char::getByteCount(static_cast<u8>(str.at(endPos)));
        length += static_cast<std::size_t>(wts8width(str.c_str() + endPos, lastCharSize));
        endPos += lastCharSize;
    }

    if (length > pos + count) {

        result += str.substr(startPos, endPos - (startPos + lastCharSize));

        // If end position is in the middle of a double width character,
        // substitute with a white space
        result += " ";

    } else {

        result += str.substr(startPos, endPos - startPos);
    }

    return result;
}


std::size_t ConsoleString::getByteCountForConsoleSize(const std::string& str,
                                                      std::size_t size) {

    for (std::size_t ii = 0; ii < str.size(); ii += Utf8Char::getByteCount(static_cast<u8>(str.at(ii)))) {

        const int len = wts8width(str.c_str(), ii);

        if (len >= static_cast<int>(size))
            return ii;
    }

    return str.size();
}
