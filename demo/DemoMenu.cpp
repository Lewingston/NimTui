
#include "DemoMenu.h"
#include "DemoStyle.h"

#include <algorithm>

using namespace TUI;


DemoMenu::DemoMenu(Vec2<s32> pos,
                   Vec2<u32> size,
                   const std::vector<std::string>& elements) :
    DemoPage(pos, size)
{
    setBackColor(DEMO_STYLE.primaryBackColor);

    setMenu();

    menu.setStyle(DEMO_STYLE);

    for (const auto& element : elements)
        menu.addElement(element);
}


void DemoMenu::draw(RenderBuffer& buffer, Vec2<s32> offset) {

    Widget::draw(buffer, offset);

    menu.draw(buffer, getPos() + offset);
}


void DemoMenu::onResize(Vec2<u32>, Vec2<u32>) {

    setMenu();
}


void DemoMenu::onSelection(const std::function<void(const std::string&)>& callback) {

    onSelectionCallback = callback;
}


void DemoMenu::setMenu() {

    const u32 width = std::min(35u, getSize().getWidth() / 3);

    const u32 maxHeight = menu.getElementHeight() * menu.getElementCount();
    const u32 minHeight = getSize().getHeight();
    const u32 height = std::min(minHeight, maxHeight);

    const s32 posX = (static_cast<s32>(getSize().getWidth()) - static_cast<s32>(width)) / 2;
    const s32 posY = (static_cast<s32>(getSize().getHeight()) - static_cast<s32>(height)) / 2;

    menu.setSize({width, height});
    menu.setPos(Vec2<s32>(posX, posY));
}


bool DemoMenu::handleKeyEvent(Console::KeyEvent keyEvent) {

    if (DemoPage::handleKeyEvent(keyEvent))
        return true;

    if (!keyEvent.pressed)
        return false;

    switch (keyEvent.keyCode) {

        case KeyCode::J:
        case KeyCode::DOWN: {
            moveCursor(1);
            return true;
        }
        case KeyCode::K:
        case KeyCode::UP: {
            moveCursor(-1);
            return true;
        }
        case KeyCode::ENTER:
        case KeyCode::O: {
            selectItem();
            return true;
        }
        default: {
            return false;
        }
    }
}


void DemoMenu::moveCursor(s32 steps) {

    menu.moveCursor(steps);
}


void DemoMenu::selectItem() {

    if (onSelectionCallback)
        onSelectionCallback(menu.getSelectedElement());
}
