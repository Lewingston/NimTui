#pragma once

#include "Widget.h"

#include <vector>
#include <string>

namespace TUI {

    class SelectionMenu : public Widget {

        public:

            SelectionMenu(Vec2<s32> pos, Vec2<u32> size);

            virtual ~SelectionMenu() = default;

            void addElement(const std::string& element);

            void draw(RenderBuffer& buffer, Vec2<s32> offset) override;

        private:

            void drawElements(RenderBuffer& buffer, Vec2<s32> offset);

            void drawElement(const std::string& element,
                             RenderBuffer& buffer,
                             Vec2<s32> offset,
                             u32 index);

            static constexpr s32 ELEMENT_HEIGHT = 3;

            std::vector<std::string> elements;

            Color borderColor = Color(0x112240ff);
            Color textColor = Color(0xac720fff);
    };
}
