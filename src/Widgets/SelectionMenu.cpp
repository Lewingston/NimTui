
#include "SelectionMenu.h"
#include "Primitives/Rect.h"
#include "Primitives/Text.h"

#include <algorithm>

using namespace TUI;


SelectionMenu::SelectionMenu(Vec2<s32> pos, Vec2<u32> size) :
    Widget(pos, size) {}


void SelectionMenu::addElement(const std::string& element) {

    elements.push_back(element);
}


void SelectionMenu::draw(RenderBuffer& buffer, Vec2<s32> offset) {

    drawElements(buffer, getPos() + offset);
}


void SelectionMenu::drawElements(RenderBuffer& buffer, Vec2<s32> offset) {

    s32 offsetY = 0;
    for (u32 ii = 0; ii < elements.size(); ii++) {

        drawElement(elements[ii],
                    buffer,
                    offset + Vec2<s32>(0, offsetY),
                    ii,
                    ii == selectedElementIndex);

        offsetY += static_cast<s32>(elementHeight);
    }
}


void SelectionMenu::drawElement(const std::string& element,
                                RenderBuffer&      buffer,
                                Vec2<s32>          offset,
                                u32                index,
                                bool               selected) {

    Rect rect(offset, {getSize().getWidth(), elementHeight});
    rect.setBackColor(style.backgroundColor);
    rect.setBorder({Rect::Border::MEDIUM, style.borderElementColor});
    rect.setBorderInset(Rect::BorderInset::VERTICAL);

    if (index != 0) {

        rect.setBorderTop({Rect::Border::THIN, style.borderElementColor});
    }

    if (index != elements.size() - 1) {

        rect.setBorderBottom({Rect::Border::THIN, style.borderElementColor});
    }

    rect.draw(buffer);

    Text text(element, offset + Vec2<s32>(static_cast<s32>(getSize().getWidth()) / 2, 1), Text::Align::CENTER);
    text.setFrontColor(selected ? style.text.selected.color : style.text.color);
    text.setBackColor(selected ? style.text.selected.backgroundColor : style.text.backgroundColor);
    text.draw(buffer);
}


void SelectionMenu::moveCursor(s32 steps) {

    if (elements.size() == 0)
        return;

    const s32 newIndex = static_cast<s32>(selectedElementIndex) + steps;
    selectedElementIndex = static_cast<u32>(std::clamp(newIndex, 0, static_cast<s32>(elements.size() - 1)));
}


const std::string& SelectionMenu::getSelectedElement() const {

    static const std::string invalid;

    if (elements.size() > 0)
        return elements.at(selectedElementIndex);
    else
        return invalid;
}
