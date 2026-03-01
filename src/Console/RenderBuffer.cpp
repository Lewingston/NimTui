
#include "RenderBuffer.h"
#include "ConsoleSequences.h"

#include <limits>
#include <optional>

using namespace TUI;


RenderBuffer::RenderBuffer(Vec2<u32> size) :
    size(size),
    characters(size.getArea()),
    dirty(size.getArea(), true) { }


void RenderBuffer::set(Vec2<u32> pos, const CharData& charData) {

    const std::size_t index = posToIndex(pos);
    if (index >= characters.size())
        return;

    /*
    if (characters[index] == charData)
        return;
    */

    characters[index] = CharData(
        charData.grapheme,
        charData.frontColor,
        characters[index].backColor.overlay(charData.backColor)
    );

    dirty[index] = true;
}


void RenderBuffer::setInverted(Vec2<u32> pos, const CharData& charData) {

    const std::size_t index = posToIndex(pos);
    if (index >= characters.size())
        return;

    set(pos, CharData(
        charData.grapheme,
        characters[index].backColor.overlay(charData.backColor),
        charData.frontColor
    ));
}


const RenderBuffer::CharData& RenderBuffer::get(Vec2<u32> pos) const {

    const std::size_t index = posToIndex(pos);

    if (index >= characters.size()) {
        static const CharData invalid;
        return invalid;
    }

    return characters.at(index);
}


std::string RenderBuffer::createTerminalSequence() {

    std::string seq;

    bool moveCursor = true;
    bool skipNextChar = false;

    std::optional<Color> frontColor;
    std::optional<Color> backColor;

    for (u32 y = 0; y < size.getHeight(); y++) {
        for (u32 x = 0; x < size.getWidth(); x++) {

            const std::size_t index = posToIndex({ x, y });

            if (skipNextChar) {
                skipNextChar = false;
                dirty[index] = false;
                continue;
            }

            if (!dirty[index]) {
                moveCursor = true;
                continue;
            }

            if (moveCursor) {
                seq += ConsoleSequences::setCursorPos(x, y);
            }

            const CharData& charData = characters[index];

            // If the current character is full width, skip the next character
            if (charData.grapheme.isFullWidth()) {
                skipNextChar = true;
            }

            // Change the front color if required
            if (!frontColor.has_value() || frontColor.value() != charData.frontColor) {

                frontColor =  charData.frontColor;
                seq += ConsoleSequences::setFrontColor(charData.frontColor);
            }

            // Change the back color if required
            if (!backColor.has_value() || backColor.value() != charData.backColor) {

                backColor = charData.backColor;
                seq += ConsoleSequences::setBackColor(charData.backColor);
            }

            // Print the current character
            seq += charData.grapheme.getStr();

            moveCursor = false;
            dirty[index] = false;
        }
    }

    return seq;
}


std::size_t RenderBuffer::posToIndex(Vec2<u32> pos) const noexcept {

    if (pos.getX() >= size.getWidth() ||
        pos.getY() >= size.getHeight())
        return std::numeric_limits<std::size_t>::max();

    return size.getWidth() * pos.getY() + pos.getX();
}
