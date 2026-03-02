
#include "Demo.h"
#include "Console/RenderBuffer.h"
#include "DemoStyle.h"

#include <iostream>

using namespace TUI;


Demo::Demo() :
    currentDemoPage(demoMenu)
{
    setupWindow();

    setupDemoMenu(demoMenu);
    setupDemoMenu(primitivesMenu);
    setupDemoMenu(widgetsMenu);

    setupDemoPage(rectDemo);
    setupDemoPage(imageBrowser);
}


void Demo::setupWindow() {

    window.onKeyInput([this](Console::KeyEvent keyEvent) {

        onKeyEvent(keyEvent);
    });

    window.onResize([this]() {

        onResize();
    });
}


void Demo::setupDemoMenu(DemoMenu& menu) {

    menu.onLeave([&]() {

        leaveDemoPage();
    });

    menu.onSelection([&](const std::string& item) {

        demoSelected(item);
    });

    menu.setStyle(DEMO_STYLE);
}


void Demo::setupDemoPage(DemoPage& page) {

    page.onLeave([&]() {

        leaveDemoPage();
    });

    page.setStyle(DEMO_STYLE);
}


void Demo::run() {

    window.show();

    while (!terminate) {

        window.readConsoleInput();

        draw();
    }

    window.hide();
}


void Demo::draw() {

    auto& renderBuffer = *window.getRenderBuffer().lock();

    currentDemoPage.get().draw(renderBuffer, {0, 0});

    const auto seq = renderBuffer.createTerminalSequence();
    std::cout << seq;
}


void Demo::onKeyEvent(Console::KeyEvent keyEvent) {

    currentDemoPage.get().handleKeyEvent(keyEvent);
}


void Demo::onResize() {

    currentDemoPage.get().setSize(window.getSize());
}


void Demo::leaveDemoPage() {

    if (&currentDemoPage.get() == &demoMenu) {

        terminate = true;

    } else {

        if (&currentDemoPage.get() == &rectDemo) {
            currentDemoPage = primitivesMenu;
        } else {
            currentDemoPage = demoMenu;
        }

        currentDemoPage.get().setSize(window.getSize());
    }
}


void Demo::demoSelected(const std::string& demo) {

    if (&currentDemoPage.get() == &demoMenu) {

        if (demo == "Primitives") {
            currentDemoPage = primitivesMenu;
        } else if (demo == "Widgets") {
            currentDemoPage = widgetsMenu;
        } else if (demo == "Image Browser") {
            currentDemoPage = imageBrowser;
        }

    } else if (&currentDemoPage.get() == &primitivesMenu) {

        if (demo == "Line") {

        } else if (demo == "Rect") {
            currentDemoPage = rectDemo;
        } else if (demo == "Text") {

        }

    } else if (&currentDemoPage.get() == &widgetsMenu) {

    }

    currentDemoPage.get().setSize(window.getSize());
}
