#pragma once

#include "Drawable.h"
#include "Color.h"

#include <string>
#include <vector>

namespace TUI {

    class Text : public Drawable {

        public:

            enum class Align : u8 {

                TOP_LEFT,
                TOP_CENTER,
                TOP_RIGHT,
                CENTER_LEFT,
                CENTER,
                CENTER_RIGHT,
                BOTTOM_LEFT,
                BOTTOM_CENTER,
                BOTTOM_RIGHT
            };

            Text(const std::string& text, Vec2<s32> pos, Align align = Align::TOP_LEFT);

            void setFrontColor(Color color) { frontColor = color; }
            void setBackColor(Color color) { backColor = color; }

            void setBlockAlign(bool block) { blockAlign = block; }

            void draw(RenderBuffer& buffer) const override;

        private:

            void drawLine(const std::string& line, u32 lineIndex, RenderBuffer& buffer) const;

            [[nodiscard]] bool checkBounds(Vec2<s32> pos, Vec2<u32> bufferSize) const;

            [[nodiscard]] Vec2<s32> getLinePos(u32 lineIndex) const;
            [[nodiscard]] s32 getLinePosX(u32 lineIndex) const;
            [[nodiscard]] s32 getLinePosY(u32 lineIndex) const;

            [[nodiscard]] static std::vector<std::string> splitTextInLines(const std::string& text);
            [[nodiscard]] static u32 calculateMaxWidth(const std::vector<std::string>& lines);

            std::vector<std::string> lines;

            Color frontColor = Color::WHITE;
            Color backColor = Color::BLACK;

            u32 maxWidth = 0;

            Align align = Align::TOP_LEFT;

            bool blockAlign = false;
    };
}
