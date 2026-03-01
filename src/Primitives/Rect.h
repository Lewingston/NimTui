#pragma once

#include "Drawable.h"
#include "Color.h"

namespace TUI {

    class Rect : public Drawable {

        public:

            enum class Border : u8 {

                VERY_THICK = 0,
                THICK,
                MEDIUM,
                THIN,
                NONE
            };

            enum class BorderInset : u8 {
                HORIZONTAL,
                VERTICAL
            };

            Rect(Vec2<s32> pos, Vec2<u32> size);

            virtual ~Rect() = default;

            void draw(RenderBuffer& buffer) const override;

            void setBorder(Border border) { this->border = border; }
            void setBorderInset(BorderInset inset) { borderInset = inset; }

            void setBackColor(Color color)   { backColor = color;   }
            void setBorderColor(Color color) { borderColor = color; }

            [[nodiscard]] bool hasBorder() const noexcept { return border != Border::NONE; }

        private:

            void fillin(RenderBuffer& buffer) const;

            void drawBorder(RenderBuffer& buffer) const;

            [[nodiscard]] bool horizontalInset() const noexcept { return borderInset == BorderInset::HORIZONTAL; }

            Vec2<u32> size;

            Border border = Border::NONE;
            BorderInset borderInset = BorderInset::HORIZONTAL;

            Color borderColor = Color::BLACK;
            Color backColor   = Color::WHITE;

    };
}
