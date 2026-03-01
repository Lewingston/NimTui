
#include "Rect.h"
#include "Console/RenderBuffer.h"
#include "Line.h"

#include <array>

using namespace TUI;


Rect::Rect(Vec2<s32> pos, Vec2<u32> size) :
    Drawable(pos), size(size) { }


void Rect::draw(RenderBuffer& buffer) const {

    if (hasBorder()) {

        drawBorder(buffer);
    }

    fillin(buffer);
}


void Rect::fillin(RenderBuffer& buffer) const {

    const Vec2<s32> borderOffset = hasBorder() ? Vec2<s32>(1, 1) : Vec2<s32>(0, 0);

    const Vec2<s32> pos = getPos() + borderOffset;

    /*
    const Vec2<s32> pos = [&]() -> Vec2<s32> {

        if (!hasBorder())
            return getPos();

        if (borderInset == BorderInset::HORIZONTAL)
            return getPos() + Vec2<s32>(1, 0);
        else
            return getPos() + Vec2<s32>(0, 1);
    }();

    const Vec2<s32> endPos = [&]() -> Vec2<s32> {

        if (!hasBorder())
            return getPos() + static_cast<Vec2<s32>>(size);

        if (borderInset == BorderInset::HORIZONTAL)
            return getPos() + static_cast<Vec2<s32>>(size) + Vec2<s32>(0, -2);
        else
            return getPos() + static_cast<Vec2<s32>>(size) + Vec2<s32>(-2, 0);

    }();
    */

    const Vec2<s32> endPos = pos +
                             static_cast<Vec2<s32>>(size) -
                             borderOffset * 2;

    for (s32 y = pos.getY(); y < endPos.getY(); y++) {
        for (s32 x = pos.getX(); x < endPos.getX(); x++) {

            buffer.set(Vec2<s32>(x, y), { " ", borderColor, backColor});
        }
    }
}


void Rect::drawBorder(RenderBuffer& buffer) const {

    const std::array horizontalElements1 = {
        "▄", "▃", "▂ ", "▁"
    };

    const std::array horizontalElements2 = {
        "▄", "▅", "▆", "▇"
    };

    const std::array verticalElements1 = {
        "█", "▊", "▌", "▎"
    };

    const std::array verticalElements2 = {
        " ", "▎", "▌", "▊"
    };

    const u8 eleIndex = static_cast<u8>(border);

    const Vec2<s32> topBorderStartPos = getPos() + (horizontalInset() ? Vec2<s32>(0, 0) : Vec2<s32>(1, 0));
    const u32 horizontalBorderLength = size.getX() - (horizontalInset() ? 0 : 2);

    Line topBorder(topBorderStartPos,
                   horizontalBorderLength,
                   horizontalInset() ?
                       horizontalElements1.at(eleIndex) :
                       horizontalElements2.at(eleIndex),
                   Line::Mode::HORIZONTAL);
    topBorder.setFrontColor(horizontalInset() ? borderColor : backColor);
    topBorder.setBackColor(horizontalInset() ? Color::TRANSP : borderColor);

    topBorder.draw(buffer);

    const Vec2<s32> bottomBorderStartPos = topBorderStartPos + Vec2<s32>(0, static_cast<s32>(size.getHeight()) - 1);

    Line bottomBorder(bottomBorderStartPos,
                      horizontalBorderLength,
                      horizontalInset() ?
                          horizontalElements2.at(eleIndex) :
                          horizontalElements1.at(eleIndex),
                      Line::Mode::HORIZONTAL);
    bottomBorder.setFrontColor(borderColor);
    bottomBorder.setBackColor(horizontalInset() ? Color::TRANSP : backColor);
    bottomBorder.setInversion(horizontalInset());

    bottomBorder.draw(buffer);

    const Vec2<s32> leftBorderStartPos = getPos() + (horizontalInset() ? Vec2<s32>(0, 1) : Vec2<s32>(0, 0));
    const u32 verticalBorderLength = size.getY() - (horizontalInset() ? 2 : 0);

    Line leftBorder(leftBorderStartPos,
                    verticalBorderLength,
                    horizontalInset() ?
                        verticalElements1.at(eleIndex) :
                        verticalElements2.at(eleIndex),
                    Line::Mode::VERTICAL);
    leftBorder.setFrontColor(borderColor);
    leftBorder.setBackColor(horizontalInset() ? backColor : Color::TRANSP);
    leftBorder.setInversion(!horizontalInset());

    leftBorder.draw(buffer);

    const Vec2<s32> rightBorderStartPos = leftBorderStartPos + Vec2<s32>(static_cast<s32>(size.getWidth()) - 1, 0);

    Line rightBorder(rightBorderStartPos,
                     verticalBorderLength,
                     horizontalInset() ?
                        verticalElements2.at(eleIndex) :
                        verticalElements1.at(eleIndex),
                    Line::Mode::VERTICAL);
    rightBorder.setFrontColor(horizontalInset() ? backColor : borderColor);
    rightBorder.setBackColor(horizontalInset() ? borderColor : Color::TRANSP);

    rightBorder.draw(buffer);
}
