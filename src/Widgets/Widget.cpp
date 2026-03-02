
#include "Widget.h"
#include "Console/RenderBuffer.h"

using namespace TUI;


Widget::Widget(Vec2<s32> pos, Vec2<u32> size) :
    pos(pos), size(size) {

}


void Widget::setSize(Vec2<u32> size) {

    const auto oldSize = this->size;
    this->size = size;

    onResize(oldSize, size);
}


void Widget::setPos(Vec2<s32> pos) {

    this->pos = pos;
}


void Widget::draw(RenderBuffer& buffer, Vec2<s32> offset) {

    for (s32 y = 0; y < static_cast<s32>(size.getHeight()); y++) {
        for (s32 x = 0; x < static_cast<s32>(size.getWidth()); x++) {

            const s32 posX = pos.getX() + x + offset.getX();
            const s32 posY = pos.getY() + y + offset.getY();

            const Vec2<u32> pos = { static_cast<u32>(posX), static_cast<u32>(posY) };

            buffer.set(pos, {
                " ",
                buffer.get(pos).frontColor,
                backColor
            });
        }
    }
}


void Widget::onResize(Vec2<u32>, Vec2<u32>) {

}


bool Widget::handleKeyEvent(Console::KeyEvent) {

    return false;
}
