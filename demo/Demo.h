#pragma once

#include "DemoMenu.h"
#include "Console/ConsoleWindow.h"

namespace TUI {

    class Demo {

        public:

            Demo();

            void run();

        private:

            void setupWindow();
            void setupDemoMenu(DemoMenu& menu);

            void draw();

            void onKeyEvent(Console::KeyEvent keyEvent);

            void onResize();

            void leaveDemoPage();

            void demoSelected(const std::string& demo);

            ConsoleWindow window;

            DemoMenu demoMenu = DemoMenu({0, 0}, window.getSize(), {
                "Primitives",
                "Widgets",
                "Image Browser",
                "Mandelbrot",
                "Game of Life",
                "Stock Chart"
            });

            DemoMenu primitivesMenu = DemoMenu({0, 0}, window.getSize(), {
                "Line",
                "Rect",
                "Text"
            });

            DemoMenu widgetsMenu = DemoMenu({0, 0}, window.getSize(), {
                "Buttons",
                "TextBox"
            });

            std::reference_wrapper<Widget> currentDemoPage;

            bool terminate = false;

    };
}
