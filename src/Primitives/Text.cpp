
#include "Text.h"
#include "Console/RenderBuffer.h"
#include "Common/Unicode.h"

#include <ranges>

using namespace TUI;


Text::Text(const std::string& text, Vec2<s32> pos, Align align) :
    Drawable(pos),
    lines(splitTextInLines(text)),
    maxWidth(calculateMaxWidth(lines)),
    align(align) {}


void Text::draw(RenderBuffer& buffer) const {

    for (u32 ii = 0; ii < lines.size(); ii++) {

        drawLine(lines[ii], ii,  buffer);
    }
}


void Text::drawLine(const std::string& line,
                    u32 lineIndex,
                    RenderBuffer& buffer) const {

    auto pos = getLinePos(lineIndex);

    for (u32 ii = 0; ii < line.size();) {

        const auto info = Unicode::getInfo(line, ii);
        const std::string str = line.substr(ii, info.byteCount);

        if (checkBounds(pos, buffer.getSize())) {

            buffer.set(pos, { str, frontColor, backColor });
        }

        ii += info.byteCount;

        pos += Vec2<s32>(info.width, 0);
    }
}


bool Text::checkBounds(Vec2<s32> pos, Vec2<u32> bufferSize) const {

    return pos.getX() >= 0 &&
           pos.getY() >= 0 &&
           pos.getX() < static_cast<s32>(bufferSize.getWidth()) &&
           pos.getY() < static_cast<s32>(bufferSize.getHeight());
}


Vec2<s32> Text::getLinePos(u32 lineIndex) const {

    return Vec2<s32>(getLinePosX(lineIndex), getLinePosY(lineIndex));
}


s32 Text::getLinePosX(u32 lineIndex) const {

    const std::string& line = lines[lineIndex];
    const s32 refWidth = blockAlign ? static_cast<s32>(maxWidth) :
                                      static_cast<s32>(line.size());

    switch (align) {

        case Align::TOP_LEFT:
        case Align::CENTER_LEFT:
        case Align::BOTTOM_LEFT:
        default: {

            return getPos().getX();
        }

        case Align::TOP_CENTER:
        case Align::CENTER:
        case Align::BOTTOM_CENTER: {

            return getPos().getX() - refWidth / 2;
        }

        case Align::TOP_RIGHT:
        case Align::CENTER_RIGHT:
        case Align::BOTTOM_RIGHT: {

            return getPos().getX() - refWidth;
        };
    }
}


s32 Text::getLinePosY(u32 lineIndex) const {

    const s32 linePos = static_cast<s32>(lineIndex);

    switch (align) {

        case Align::TOP_LEFT:
        case Align::TOP_CENTER:
        case Align::TOP_RIGHT:
        default: {

            return getPos().getY() + linePos;
        }

        case Align::CENTER_LEFT:
        case Align::CENTER:
        case Align::CENTER_RIGHT: {

            const s32 centerOffset = static_cast<s32>(lines.size()) / 2;
            return getPos().getY() + linePos - centerOffset;
        }

        case Align::BOTTOM_LEFT:
        case Align::BOTTOM_CENTER:
        case Align::BOTTOM_RIGHT: {

            return getPos().getY() - static_cast<s32>(lines.size()) + linePos;
        }
    };
}


std::vector<std::string> Text::splitTextInLines(const std::string& text) {

    std::vector<std::string> result;

    for (auto line : text | std::views::split('\n')) {

        result.emplace_back(line.begin(), line.end());
    }

    return result;
}


u32 Text::calculateMaxWidth(const std::vector<std::string>& lines) {

    u32 maxWidth = 0;
    for (const auto& line : lines) {

        if (line.size() > maxWidth)
            maxWidth = static_cast<u32>(line.size());
    }

    return maxWidth;
}
