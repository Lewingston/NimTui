
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

    characters[index] = charData;
    dirty[index] = true;
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
    std::optional<Color> frontColor;
    std::optional<Color> backColor;

    for (u32 y = 0; y < size.getHeight(); y++) {
        for (u32 x = 0; x < size.getWidth(); x++) {

            const std::size_t index = posToIndex({ x, y });

            if (!dirty[index]) {
                moveCursor = true;
                continue;
            }

            if (moveCursor) {
                seq += ConsoleSequences::setCursorPos(x, y);
            }

            const CharData& charData = characters[index];

            if (!frontColor.has_value() || frontColor.value() != charData.frontColor) {

                frontColor =  charData.frontColor;
                seq += ConsoleSequences::setFrontColor(charData.frontColor);
            }

            if (!backColor.has_value() || backColor.value() != charData.backColor) {

                backColor = charData.backColor;
                seq += ConsoleSequences::setBackColor(charData.backColor);
            }

            seq += charData.character;

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
