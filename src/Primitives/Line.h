#pragma once

#include "Drawable.h"
#include "Color.h"

#include <string>

namespace TUI {

    class Line : public Drawable {

        public:

            enum class Mode : u8 {
                HORIZONTAL,
                VERTICAL
            };

            Line(Vec2<s32> pos, u32 length, const std::string& seq, Mode mode);

            virtual ~Line() = default;

            void draw(RenderBuffer& buffer) const override;

            void setFrontColor(Color color) { frontColor = color; }
            void setBackColor(Color color) { backColor  = color; }

        private:

            void drawHorizontal(RenderBuffer& buffer) const;
            void drawVertical(RenderBuffer& buffer) const;

            std::string seq = "#";

            u32 length = 0;
            Mode mode = Mode::HORIZONTAL;

            Color frontColor = Color::BLACK;
            Color backColor  = Color::WHITE;
    };
}
