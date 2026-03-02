
#include "ImageBrowser.h"

#include <algorithm>

using namespace TUI;


ImageBrowser::ImageBrowser(Vec2<s32> pos, Vec2<u32> size) :
    DemoPage(pos, size) {}


void ImageBrowser::draw(RenderBuffer& renderBuffer, Vec2<s32> offset) {

    DemoPage::draw(renderBuffer, offset);

    fileBrowser.draw(renderBuffer, offset + getPos());
}


bool ImageBrowser::handleKeyEvent(Console::KeyEvent keyEvent) {

    if (DemoPage::handleKeyEvent(keyEvent))
        return true;

    if (!keyEvent.pressed)
        return false;

    switch (keyEvent.keyCode) {

        case KeyCode::J:
        case KeyCode::DOWN: {
            fileBrowser.moveCursor(1);
            return true;
        }
        case KeyCode::K:
        case KeyCode::UP: {
            fileBrowser.moveCursor(-1);
            return true;
        }
        case KeyCode::ENTER:
        case KeyCode::O: {
            fileBrowser.enter();
            return true;
        }
        case KeyCode::MINUS : {
            fileBrowser.leave();
            return true;
        }
        case KeyCode::LEFT:
        case KeyCode::H: {
            return true;
        }
        case KeyCode::RIGHT:
        case KeyCode::L: {
            return true;
        }
        default: {
            return false;
        }
    }

    return false;
}


void ImageBrowser::onResize() {

    const u32 width = std::min(30u, static_cast<u32>(getSize().getWidth() * 0.25));
    fileBrowser.setSize({width, getSize().getHeight()});
}
