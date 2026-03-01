
#include "Line.h"
#include "Console/RenderBuffer.h"

using namespace TUI;


Line::Line(Vec2<s32> pos, u32 length, const std::string& seq, Mode mode) :
    Drawable(pos),
    seq(seq),
    length(length),
    mode(mode) {}


void Line::draw(RenderBuffer& buffer) const {

    if (mode == Mode::HORIZONTAL) {

        drawHorizontal(buffer);

    } else {

        drawVertical(buffer);
    }
}


void Line::drawHorizontal(RenderBuffer& buffer) const {

    const s32 endPos = getPos().getX() + static_cast<s32>(length);

    for (s32 x = getPos().getX(); x < endPos; x++) {

        buffer.set(Vec2<s32>(x, getPos().getY()), {
            seq,
            frontColor,
            backColor
        });
    }
}


void Line::drawVertical(RenderBuffer& buffer) const {

    const s32 endPos = getPos().getY() + static_cast<s32>(length);

    for (s32 y = getPos().getY(); y < endPos; y++) {

        buffer.set(Vec2<s32>(getPos().getX(), y), {
            seq,
            frontColor,
            backColor
        });
    }
}
