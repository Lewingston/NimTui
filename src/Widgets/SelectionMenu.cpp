
#include "SelectionMenu.h"
#include "Primitives/Rect.h"
#include "Primitives/Text.h"

using namespace TUI;


SelectionMenu::SelectionMenu(Vec2<s32> pos, Vec2<u32> size) :
    Widget(pos, size) {

    setBackColor(0x060a1dff);
}


void SelectionMenu::addElement(const std::string& element) {

    elements.push_back(element);
}


void SelectionMenu::draw(RenderBuffer& buffer, Vec2<s32> offset) {

    drawElements(buffer, getPos() + offset);
}


void SelectionMenu::drawElements(RenderBuffer& buffer, Vec2<s32> offset) {

    s32 offsetY = 0;
    for (u32 ii = 0; ii < elements.size(); ii++) {

        drawElement(elements[ii], buffer, offset + Vec2<s32>(0, offsetY), ii);

        offsetY += ELEMENT_HEIGHT;
    }
}


void SelectionMenu::drawElement(const std::string& element,
                                RenderBuffer& buffer,
                                Vec2<s32> offset,
                                u32 index) {

    Rect rect(offset, {getSize().getWidth(), ELEMENT_HEIGHT});
    rect.setBackColor(getBackColor());
    rect.setBorder({Rect::Border::MEDIUM, borderColor});
    rect.setBorderInset(Rect::BorderInset::VERTICAL);

    if (index != 0) {

        rect.setBorderTop({Rect::Border::THIN, borderColor});
    }

    if (index != elements.size() - 1) {

        rect.setBorderBottom({Rect::Border::THIN, borderColor});
    }

    rect.draw(buffer);

    Text text(element, offset + Vec2<s32>(getSize().getWidth() / 2, 1), Text::Align::CENTER);
    text.setFrontColor(textColor);
    text.setBackColor(getBackColor());
    text.draw(buffer);
}
