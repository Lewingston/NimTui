#pragma once

#include "Vec.h"
#include "Types.h"

namespace TUI {

    class RenderBuffer;

    class Drawable {

        public:

            Drawable(Vec2<s32> pos);

            virtual ~Drawable() = default;

            virtual void draw(RenderBuffer& buffer) const = 0;

            [[nodiscard]] const Vec2<s32>& getPos() const noexcept { return pos; }

        private:

            Vec2<s32> pos;
    };
}
