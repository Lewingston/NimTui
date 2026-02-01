
#include "ConsoleWindow.h"
#include "RenderBuffer.h"

using namespace TUI;


ConsoleWindow::ConsoleWindow() {

    const Vec2<u32> size = console.readConsoleSize();

    renderBuffer = std::make_shared<RenderBuffer>(size);
}


std::weak_ptr<RenderBuffer> ConsoleWindow::getRenderBuffer() {

    return renderBuffer;
}


const Vec2<u32>& ConsoleWindow::getSize() const {

    return renderBuffer->getSize();
}


void ConsoleWindow::show() {

    console.hideCursor();
    console.enterAlternateMode();
    console.enableConsoleWindowInputEvents();
}


void ConsoleWindow::hide() {

    console.leaveAlternateMode();
    console.showCursor();
}


void ConsoleWindow::onResize(std::function<void()> onResizeCallback) {

    this->onResizeCallback = onResizeCallback;
}


void ConsoleWindow::onKeyInput(std::function<void(Console::KeyEvent)> onKeyInputCallback) {

    this->onKeyInputCallback = onKeyInputCallback;
}


void ConsoleWindow::readConsoleInput() {

    const auto inputEvent = console.readConsoleInput();
    if (!inputEvent.has_value())
        return;

    handleConsoleInputEvent(inputEvent.value());
}


void ConsoleWindow::handleConsoleInputEvent(const Console::InputEvent& inputEvent) {

    if (std::holds_alternative<Console::ResizeEvent>(inputEvent.event)) {

        handleResizeEvent(std::get<Console::ResizeEvent>(inputEvent.event));

    } else if (std::holds_alternative<Console::KeyEvent>(inputEvent.event)) {

        handleKeyEvent(std::get<Console::KeyEvent>(inputEvent.event));
    }
}


void ConsoleWindow::handleKeyEvent(const Console::KeyEvent& keyEvent) {

    if (onKeyInputCallback)
        onKeyInputCallback(keyEvent);
}


void ConsoleWindow::handleResizeEvent(const Console::ResizeEvent& resizeEvent) {

    renderBuffer = std::make_shared<RenderBuffer>(resizeEvent.size);

    if (onResizeCallback)
        onResizeCallback();
}
