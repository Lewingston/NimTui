#pragma once

#include "Widget.h"

#include <string>

namespace TUI {

    class Grid : public Widget {

        public:

            Grid(Vec2<s32> pos, Vec2<u32> size);

            virtual ~Grid() = default;

            void draw(RenderBuffer& buffer, Vec2<s32> offset) override;

            void setColors(Color color1, Color color2);
            void setTextColor(Color color);

            void setGridSize(Vec2<u32> size);

            void enableNumbers(bool enable);

            void enableOffset(bool enable);

        private:

            void drawGrid(RenderBuffer& buffer, Vec2<s32> offset);
            void drawNumbers(RenderBuffer& buffer, Vec2<s32> offset);

            [[nodiscard]] Vec2<s32> getGridOffset() const;

            [[nodiscard]] std::string getGridText(s32 x , s32 y) const;

            Vec2<u32> gridSize { 24, 12 };

            bool showNumbers = false;
            bool offset = true;

            Color color1 = Color::WHITE;
            Color color2 = Color::BLACK;
            Color textColor = Color::WHITE;

    };
}
