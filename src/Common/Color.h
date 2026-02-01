#pragma once

#include "Types.h"

namespace TUI {

    class Color {

        public:

            static const Color WHITE;
            static const Color BLACK;
            static const Color RED;
            static const Color BLUE;
            static const Color GREEN;

            Color(u8 r, u8 g, u8 b) :
                r(r), g(g), b(b) {}

            [[nodiscard]] u8 getR() const noexcept { return r; }
            [[nodiscard]] u8 getG() const noexcept { return g; }
            [[nodiscard]] u8 getB() const noexcept { return b; }

            [[nodiscard]] bool operator==(const Color& c) const noexcept {
                return r == c.r && g == c.g && b == c.b;
            }

        private:

            u8 r = 0;
            u8 g = 0;
            u8 b = 0;

    };
}
