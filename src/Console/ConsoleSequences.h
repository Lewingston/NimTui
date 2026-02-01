#pragma once

#include "Types.h"
#include "Color.h"

#include <string_view>
#include <string>

namespace TUI {

    class ConsoleSequences {

        public:

            ConsoleSequences() = delete;
            ~ConsoleSequences() = delete;

            [[nodiscard]] static constexpr std::string_view enterAlternateMode() {

                return "\x1b[?1049h";
            }

            [[nodiscard]] static constexpr std::string_view leaveAlternateMode() {

                return "\x1b[?1049l";
            }

            [[nodiscard]] static constexpr std::string_view showCursor() {

                return "\x1b[?25h";
            }

            [[nodiscard]] static constexpr std::string_view hideCursor() {

                return "\x1b[?25l";
            }

            [[nodiscard]] static std::string setCursorPos(u32 x, u32 y) {

                return "\x1b[" + std::to_string(y) + ";" + std::to_string(x) + "H";
            }

            [[nodiscard]] static std::string setFrontColor(Color color) {

                return "\x1b[38;2;" + std::to_string(color.getR()) + ";" +
                                      std::to_string(color.getG()) + ";" +
                                      std::to_string(color.getB()) + "m";
            }

            [[nodiscard]] static std::string setBackColor(Color color) {

                return "\x1b[48;2;" + std::to_string(color.getR()) + ";" +
                                      std::to_string(color.getG()) + ";" +
                                      std::to_string(color.getB()) + "m";
            }

            [[nodiscard]] static constexpr std::string_view resetTextFormat() {

                return "\x1b[0m";
            }

    };
}
