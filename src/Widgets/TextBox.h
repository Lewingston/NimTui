#pragma once

#include "Widget.h"

#include <string>
#include <vector>

namespace TUI {

    class TextBox : public Widget {

        public:

            TextBox(Vec2<s32> pos, Vec2<u32> size);

            virtual ~TextBox() = default;

            void draw(RenderBuffer& buffer, Vec2<s32> offset) override;

            void setText(const std::string& text);
            [[nodiscard]] std::string getText() const;

            void setTextColor(Color color) { textColor = color; }
            [[nodiscard]] Color getTextColor() const noexcept { return textColor; }

        private:

            void drawTextLine(RenderBuffer& buffer, Vec2<s32> offset, const std::string& line);

            std::vector<std::string> textLines;

            Color textColor = Color::WHITE;

    };
}
