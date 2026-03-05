
#include "ImageBrowser.h"
#include "Primitives/Line.h"

using namespace TUI;
using namespace Demo;


ImageBrowser::ImageBrowser(Vec2<s32> pos, Vec2<u32> size) :
    DemoPage(pos, size) {}


void ImageBrowser::setStyle(const Style& style) {

    DemoPage::setStyle(style);

    fileBrowser.setStyle(style);
    image.setStyle(style);
}


void ImageBrowser::draw(RenderBuffer& renderBuffer, Vec2<s32> offset) {

    DemoPage::draw(renderBuffer, offset);

    fileBrowser.draw(renderBuffer, offset + getPos());

    Line line(Vec2<s32>(static_cast<s32>(fileBrowser.getSize().getWidth()), 0),
              getSize().getHeight(),
              "┃",
              Line::Mode::VERTICAL);
    line.setBackColor(getStyle().primaryBackColor);
    line.setFrontColor(getStyle().borderColor);

    line.draw(renderBuffer);

    image.draw(renderBuffer, offset + getPos());
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
        case KeyCode::U: {
            if (true /*hasFlag(keyEvent.keyModifiers, KeyModifier::CTRL_LEFT)*/) {
                fileBrowser.moveCursor(-10);
                return true;
            } else {
                return false;
            }
        }
        case KeyCode::D: {
            if (true /*hasFlag(keyEvent.keyModifiers, KeyModifier::CTRL_LEFT)*/) {
                fileBrowser.moveCursor(10);
                return true;
            } else {
                return false;
            }
        }
        case KeyCode::ENTER:
        case KeyCode::O: {
            fileSelected(fileBrowser.enter());
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

    const u32 width = std::min(45u, static_cast<u32>(getSize().getWidth() * 0.25));
    fileBrowser.setSize({width, getSize().getHeight()});

    image.setSize({getSize().getWidth() - width - 1, getSize().getHeight()});
    image.setPos({static_cast<s32>(width) + 1, 0});
}


void ImageBrowser::fileSelected(const FileBrowser::FileTreeEntry& file) {

    if (file.entryType != FileBrowser::DirEntryType::FILE)
        return;

    static constexpr std::array supportedFiles = {
        ".png", ".jpg", ".jpeg", ".PNG", ".JPG", ".JPEG"
    };

    if (std::find(supportedFiles.begin(), supportedFiles.end(), file.path.extension()) == supportedFiles.end()) {
        return;
    }

    image.loadFromFile(file.path.string());
}
