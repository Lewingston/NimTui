#pragma once

#include "Drawable.h"
#include "Color.h"

#include <string>

namespace TUI {

    class Text : public Drawable {

        public:

            Text(const std::string& text, Vec2<s32> pos);

            void setFrontColor(Color color) { frontColor = color; }
            void setBackColor(Color color) { backColor = color; }

            void draw(RenderBuffer& buffer) const override;

        private:

            [[nodiscard]] bool checkBounds(s32 posX, s32 posY, Vec2<u32> bufferSize) const;

            std::string text;

            Color frontColor = Color::WHITE;
            Color backColor = Color::BLACK;
    };
}
