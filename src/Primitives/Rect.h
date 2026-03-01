#pragma once

#include "Drawable.h"
#include "Color.h"

namespace TUI {

    class Rect : public Drawable {

        public:


            enum class BorderInset : u8 {
                HORIZONTAL,
                VERTICAL
            };

            struct Border {

                enum Style : u8 {

                    VERY_THICK = 0,
                    THICK,
                    MEDIUM,
                    THIN,
                    NONE
                };

                Border::Style style = Style::NONE;
                Color color  = Color::BLACK;

                [[nodiscard]] bool hasBorder() const noexcept { return style != Style::NONE; }
            };

            Rect(Vec2<s32> pos, Vec2<u32> size);

            virtual ~Rect() = default;

            void draw(RenderBuffer& buffer) const override;

            void setBorder(const Border& border);
            void setBorderTop(const Border& border) { borderTop = border; }
            void setBorderLeft(const Border& border) { borderLeft = border; }
            void setBorderRight(const Border& border) { borderRight = border; }
            void setBorderBottom(const Border& border) { borderBottom = border; }

            void setBorderInset(BorderInset inset) { borderInset = inset; }

            void setBackColor(Color color) { backColor = color; }

        private:

            void fillin(RenderBuffer& buffer) const;

            void drawBorder(RenderBuffer& buffer) const;

            [[nodiscard]] bool horizontalInset() const noexcept { return borderInset == BorderInset::HORIZONTAL; }

            Vec2<u32> size;

            Border borderTop;
            Border borderBottom;
            Border borderLeft;
            Border borderRight;

            BorderInset borderInset = BorderInset::HORIZONTAL;

            Color backColor   = Color::WHITE;

    };
}
