#pragma once

#include "Widget.h"
#include "Style.h"

#include <vector>
#include <string>

namespace TUI {

    class SelectionMenu : public Widget {

        public:

            SelectionMenu(Vec2<s32> pos, Vec2<u32> size);

            virtual ~SelectionMenu() = default;

            void addElement(const std::string& element);

            void setStyle(const Style& style) noexcept { this->style = style; }

            void draw(RenderBuffer& buffer, Vec2<s32> offset) override;

            void setElementHeight(u32 height) noexcept { elementHeight = height; }
            [[nodiscard]] u32 getElementHeight() const noexcept { return elementHeight; }

            [[nodiscard]] u32 getElementCount() const noexcept { return static_cast<u32>(elements.size()); }

            [[nodiscard]] const std::string& getSelectedElement() const;

            void moveCursor(s32 steps);

        private:

            void drawElements(RenderBuffer& buffer, Vec2<s32> offset);

            void drawElement(const std::string& element,
                             RenderBuffer&      buffer,
                             Vec2<s32>          offset,
                             u32                index,
                             bool               selected);

            u32 elementHeight = 3;

            u32 selectedElementIndex = 0;

            std::vector<std::string> elements;

            Style style = DEFAULT_STYLE;
    };
}
