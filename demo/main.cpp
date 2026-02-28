
#include "Console/ConsoleWindow.h"
#include "Console/RenderBuffer.h"
#include "Widgets/Grid.h"

#include <iostream>

using namespace TUI;

int main() {

    ConsoleWindow window;

    window.show();

    Grid grid({0, 0}, window.getSize());
    grid.setColors({26, 33, 46}, {33, 40, 59});
    grid.setTextColor({ 100, 114, 137 });
    grid.setGridSize({ 24, 12 });
    grid.enableNumbers(true);

    bool terminate = false;

    window.onResize([&]() {

        grid.setSize(window.getSize());
    });

    window.onKeyInput([&](Console::KeyEvent keyEvent) {

        if (!keyEvent.pressed)
            return;

        if (keyEvent.keyCode == KeyCode::ESC) {
            terminate = true;
        }
    });

    while (!terminate) {

        window.readConsoleInput();

        auto renderBuffer = window.getRenderBuffer().lock();
        grid.draw(*renderBuffer, {0, 0});

        auto seq = renderBuffer->createTerminalSequence();
        std::cout << seq;
    }

    return 0;
}
