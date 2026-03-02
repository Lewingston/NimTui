#pragma once

#include "../DemoPage.h"
#include "Widgets/FileBrowser.h"

namespace TUI {

    class ImageBrowser : public DemoPage {

        public:

            ImageBrowser(Vec2<s32> pos, Vec2<u32> size);

            virtual ~ImageBrowser() = default;

            void draw(RenderBuffer& renderBuffer, Vec2<s32> offset) override;

            bool handleKeyEvent(Console::KeyEvent keyEvent) override;

        private:

            void onResize() override;

            FileBrowser fileBrowser = FileBrowser({0, 0}, {0, 0});

    };
}
