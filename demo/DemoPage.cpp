
#include "DemoPage.h"

using namespace TUI;


DemoPage::DemoPage(Vec2<s32> pos, Vec2<u32> size) :
    Widget(pos, size) {}


void DemoPage::setStyle(const Style& style) {

    this->style = style;
}


void DemoPage::onLeave(std::function<void()> callback) {

    onLeaveCallback = callback;
}


bool DemoPage::handleKeyEvent(Console::KeyEvent keyEvent) {

    if (!keyEvent.pressed)
        return false;

    if (keyEvent.keyCode == KeyCode::ESC) {

        leaveMenu();
        return true;
    }

    return false;
}


void DemoPage::leaveMenu() {

    if (onLeaveCallback)
        onLeaveCallback();
}
