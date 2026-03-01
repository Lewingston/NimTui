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
            static const Color YELLOW;
            static const Color ORANGE;
            static const Color PURPLE;
            static const Color GRAY;

            constexpr Color(u8 r, u8 g, u8 b) :
                r(r), g(g), b(b) {}

            [[nodiscard]] constexpr u8 getR() const noexcept { return r; }
            [[nodiscard]] constexpr u8 getG() const noexcept { return g; }
            [[nodiscard]] constexpr u8 getB() const noexcept { return b; }

            [[nodiscard]] constexpr bool operator==(const Color& c) const noexcept {
                return r == c.r && g == c.g && b == c.b;
            }

        private:

            u8 r = 0;
            u8 g = 0;
            u8 b = 0;

    };
}
