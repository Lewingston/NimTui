#pragma once

#include "../DemoPage.h"
#include "Widgets/FileBrowser.h"
#include "ImageView.h"

namespace TUI {

    class ImageBrowser : public DemoPage {

        public:

            ImageBrowser(Vec2<s32> pos, Vec2<u32> size);

            virtual ~ImageBrowser() = default;

            void setStyle(const Style& style) override;

            void draw(RenderBuffer& renderBuffer, Vec2<s32> offset) override;

            bool handleKeyEvent(Console::KeyEvent keyEvent) override;

        private:

            void onResize() override;

            void fileSelected(const FileBrowser::FileTreeEntry& file);

            FileBrowser fileBrowser = FileBrowser({0, 0}, {0, 0});

            std::string message;

            ImageView image = ImageView({0, 0}, {0, 0});

    };
}
