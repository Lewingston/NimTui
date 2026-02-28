
#include "ConsoleString.h"
#include "Common/Unicode.h"

using namespace TUI;


std::string ConsoleString::getSubstring(const std::string& str,
                                        std::size_t pos,
                                        std::size_t count) {

    std::string result;

    std::size_t length = 0;

    Unicode::Info lastCharInfo;

    // Iterate over string untill we reach start position
    std::size_t startPos = 0;
    while (length < pos) {

        if (startPos >= str.length())
            break;

        const std::size_t remainingLength = str.length() - startPos;
        lastCharInfo = Unicode::getInfo(str.c_str() + startPos, remainingLength);

        length   += lastCharInfo.width;
        startPos += lastCharInfo.byteCount;
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

        const std::size_t remainingLength = str.length() - endPos;
        lastCharInfo = Unicode::getInfo(str.c_str() + endPos, remainingLength);

        length += lastCharInfo.width;
        endPos += lastCharInfo.byteCount;
    }

    if (length > pos + count) {

        result += str.substr(startPos, endPos - (startPos + lastCharInfo.byteCount));

        // If end position is in the middle of a double width character,
        // substitute with a white space
        result += " ";

    } else {

        result += str.substr(startPos, endPos - startPos);
    }

    return result;
}
