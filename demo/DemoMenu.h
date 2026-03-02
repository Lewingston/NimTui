#pragma once

#include "DemoPage.h"
#include "Widgets/SelectionMenu.h"
#include "Console/Console.h"

#include <functional>

namespace TUI {

    class DemoMenu : public DemoPage {

        public:

            DemoMenu(Vec2<s32> pos,
                     Vec2<u32> size,
                     const std::vector<std::string>& elements);

            virtual ~DemoMenu() = default;

            void setStyle(const Style& style) override;

            void draw(RenderBuffer& buffer, Vec2<s32> offset) override;

            void onSelection(const std::function<void(const std::string&)>& callback);

            bool handleKeyEvent(Console::KeyEvent keyEvent) override;

        private:

            void onResize() override;

            void setMenu();

            void moveCursor(s32 steps);

            void selectItem();

            SelectionMenu menu = SelectionMenu({0, 0}, {0, 0});

            std::function<void(const std::string&)> onSelectionCallback;
            std::function<void()> onLeaveCallback;
    };
}
