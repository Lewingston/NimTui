#pragma once

#include "Types.h"

namespace TUI {

    class Color final {

        public:

            static const Color TRANSP;
            static const Color WHITE;
            static const Color BLACK;
            static const Color RED;
            static const Color BLUE;
            static const Color GREEN;
            static const Color YELLOW;
            static const Color ORANGE;
            static const Color PURPLE;
            static const Color GRAY;

            constexpr Color(u8 r, u8 g, u8 b, u8 a = 255) :
                r(r), g(g), b(b), a(a) {}

            [[nodiscard]] constexpr u8 getR() const noexcept { return r; }
            [[nodiscard]] constexpr u8 getG() const noexcept { return g; }
            [[nodiscard]] constexpr u8 getB() const noexcept { return b; }
            [[nodiscard]] constexpr u8 getA() const noexcept { return a; }

            [[nodiscard]] constexpr bool operator==(const Color& c) const noexcept {
                return r == c.r && g == c.g && b == c.b && a == c.a;
            }

            [[nodiscard]] Color overlay(Color color) const noexcept;

        private:

            [[nodiscard]] Color multAlpha(u8 alpha) const noexcept;
            [[nodiscard]] Color add(Color color) const noexcept;

            u8 r = 0;
            u8 g = 0;
            u8 b = 0;
            u8 a = 0;

    };
}
