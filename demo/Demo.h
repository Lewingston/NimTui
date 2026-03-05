#pragma once

#include "DemoMenu.h"
#include "DemoPage.h"
#include "Console/ConsoleWindow.h"
#include "Primitives/RectDemo.h"
#include "Primitives/TextDemo.h"
#include "ImageBrowserDemo/ImageBrowser.h"

namespace TUI::Demo {

    class TuiDemo {

        public:

            TuiDemo();

            void run();

        private:

            void setupWindow();
            void setupDemoMenu(DemoMenu& menu);
            void setupDemoPage(DemoPage& page);

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
                "Stock Chart",
                "Info"
            });

            DemoMenu primitivesMenu = DemoMenu({0, 0}, window.getSize(), {
                "Line",
                "Rect",
                "Text"
            });

            DemoMenu widgetsMenu = DemoMenu({0, 0}, window.getSize(), {
                "Buttons",
                "TextBox",
                "ListView"
            });

            RectDemo rectDemo = RectDemo({0, 0}, window.getSize());
            TextDemo textDemo = TextDemo({0, 0}, window.getSize());

            ImageBrowser imageBrowser = ImageBrowser({0, 0}, window.getSize());

            std::reference_wrapper<DemoPage> currentDemoPage;

            bool terminate = false;

    };
}
