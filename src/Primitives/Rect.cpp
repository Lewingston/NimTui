
#include "Rect.h"
#include "Console/RenderBuffer.h"
#include "Line.h"

#include <array>

using namespace TUI;


Rect::Rect(Vec2<s32> pos, Vec2<u32> size) :
    Drawable(pos), size(size) { }


void Rect::draw(RenderBuffer& buffer) const {

    drawBorder(buffer);

    fillin(buffer);
}


void Rect::fillin(RenderBuffer& buffer) const {

    const s32 leftBorderOffset   = borderLeft.hasBorder()   ? 1 : 0;
    const s32 rightBorderOffset  = borderRight.hasBorder()  ? 1 : 0;
    const s32 topBorderOffset    = borderTop.hasBorder()    ? 1 : 0;
    const s32 bottomBorderOffset = borderBottom.hasBorder() ? 1 : 0;

    const s32 yStartPos = getPos().getY() + topBorderOffset;
    const s32 yEndPos   = yStartPos + static_cast<s32>(size.getHeight()) - topBorderOffset - bottomBorderOffset;

    const s32 xStartPos = getPos().getX() + leftBorderOffset;
    const s32 xEndPos   = xStartPos + static_cast<s32>(size.getWidth()) - leftBorderOffset - rightBorderOffset;

    for (s32 y = yStartPos; y < yEndPos; y++) {
        for (s32 x = xStartPos; x < xEndPos; x++) {

            buffer.set(Vec2<s32>(x, y), { " ", Color::BLACK, backColor});
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

    const Vec2<s32> topBorderStartPos = getPos() + (horizontalInset() ? Vec2<s32>(0, 0) : Vec2<s32>(1, 0));
    const u32 horizontalBorderLength = size.getX() - (horizontalInset() ? 0 : 2);

    if (borderTop.hasBorder()){

        const u8 eleIndex = static_cast<u8>(borderTop.style);

        Line topBorder(topBorderStartPos,
                       horizontalBorderLength,
                       horizontalInset() ?
                           horizontalElements1.at(eleIndex) :
                           horizontalElements2.at(eleIndex),
                       Line::Mode::HORIZONTAL);
        topBorder.setFrontColor(horizontalInset() ? borderTop.color : backColor);
        topBorder.setBackColor(horizontalInset() ? Color::TRANSP : borderTop.color);

        topBorder.draw(buffer);
    }

    if (borderBottom.hasBorder()) {

        const u8 eleIndex = static_cast<u8>(borderBottom.style);

        const Vec2<s32> bottomBorderStartPos = topBorderStartPos + Vec2<s32>(0, static_cast<s32>(size.getHeight()) - 1);

        Line bottomBorder(bottomBorderStartPos,
                          horizontalBorderLength,
                          horizontalInset() ?
                              horizontalElements2.at(eleIndex) :
                              horizontalElements1.at(eleIndex),
                          Line::Mode::HORIZONTAL);
        bottomBorder.setFrontColor(borderBottom.color);
        bottomBorder.setBackColor(horizontalInset() ? Color::TRANSP : backColor);
        bottomBorder.setInversion(horizontalInset());

        bottomBorder.draw(buffer);
    }

    const Vec2<s32> leftBorderStartPos = getPos() + (horizontalInset() ? Vec2<s32>(0, 1) : Vec2<s32>(0, 0));
    const u32 verticalBorderLength = size.getY() - (horizontalInset() ? 2 : 0);

    if (borderLeft.hasBorder()) {

        const u8 eleIndex = static_cast<u8>(borderLeft.style);

        Line leftBorder(leftBorderStartPos,
                        verticalBorderLength,
                        horizontalInset() ?
                            verticalElements1.at(eleIndex) :
                            verticalElements2.at(eleIndex),
                        Line::Mode::VERTICAL);
        leftBorder.setFrontColor(borderLeft.color);
        leftBorder.setBackColor(horizontalInset() ? backColor : Color::TRANSP);
        leftBorder.setInversion(!horizontalInset());

        leftBorder.draw(buffer);
    }

    if (borderRight.hasBorder()) {

        const u8 eleIndex = static_cast<u8>(borderRight.style);

        const Vec2<s32> rightBorderStartPos = leftBorderStartPos + Vec2<s32>(static_cast<s32>(size.getWidth()) - 1, 0);

        Line rightBorder(rightBorderStartPos,
                         verticalBorderLength,
                         horizontalInset() ?
                            verticalElements2.at(eleIndex) :
                            verticalElements1.at(eleIndex),
                        Line::Mode::VERTICAL);
        rightBorder.setFrontColor(horizontalInset() ? backColor : borderRight.color);
        rightBorder.setBackColor(horizontalInset() ? borderRight.color : Color::TRANSP);

        rightBorder.draw(buffer);
    }
}


void Rect::setBorder(const Border& border) {

    borderTop    = border;
    borderBottom = border;
    borderLeft   = border;
    borderRight  = border;
}
