
#include "Widget.h"
#include "Primitives/Rect.h"
#include "Console/RenderBuffer.h"

using namespace TUI;


Widget::Widget(Vec2<s32> pos, Vec2<u32> size) :
    pos(pos), size(size) {

}


void Widget::setSize(Vec2<u32> size) {

    this->size = size;

    onResize();
}


void Widget::setPos(Vec2<s32> pos) {

    this->pos = pos;
}


void Widget::draw(RenderBuffer& buffer, Vec2<s32> offset) {

    Rect rect(offset + getPos(), getSize());
    rect.setBackColor(backColor);

    rect.draw(buffer);
}


void Widget::onResize() {

}


bool Widget::handleKeyEvent(Console::KeyEvent) {

    return false;
}
