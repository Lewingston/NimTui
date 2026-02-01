#pragma once

#include "Vec.h"
#include "Types.h"
#include "Color.h"

namespace TUI {

    class RenderBuffer;

    class Widget {

        public:

            Widget(Vec2<s32> pos, Vec2<u32> size);

            virtual ~Widget() = default;

            void setSize(Vec2<u32> size);
            void setPos(Vec2<s32> pos);

            [[nodiscard]] Vec2<u32> getSize() const noexcept { return size; }
            [[nodiscard]] Vec2<s32> getPos() const noexcept { return pos; }

            void setBackColor(Color color) { backColor = color; }
            [[nodiscard]] Color getBackColor() const noexcept { return backColor; }

            virtual void draw(RenderBuffer& buffer, Vec2<s32> offset);

        private:

            Vec2<s32> pos;
            Vec2<u32> size;

            Color backColor = Color::BLACK;

    };
}
