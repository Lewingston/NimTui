#pragma once

#include "Types.h"

#include <array>
#include <string>
#include <limits>

namespace TUI {

    class Utf8Char final {

        public:

            constexpr Utf8Char() = default;


            constexpr Utf8Char(const char* str) {

                const u8 count = getByteCount(static_cast<u8>(str[0]));
                if (count > 4)
                    return;

                for (u8 ii = 0; ii < count; ii++) {
                    bytes[ii] = static_cast<u8>(str[ii]);
                }
            };


            [[nodiscard]] static constexpr u8 getByteCount(const u8 firstByte) noexcept {

                if (firstByte == 0)
                    return 0;
                else if ((firstByte & 0b1000'0000) == 0)
                    return 1;
                else if ((firstByte & 0b1110'0000) == 0b1100'0000)
                    return 2;
                else if ((firstByte & 0b1111'0000) == 0b1110'0000)
                    return 3;
                else if ((firstByte & 0b1111'1000) == 0b1111'0000)
                    return 4;

                return std::numeric_limits<u8>::max();
            }


            [[nodiscard]] constexpr u8 getByteCount() const noexcept {

                return getByteCount(bytes[0]);
            }


            [[nodiscard]] constexpr const std::array<u8, 4> getBytes() const noexcept {

                return bytes;
            }


            [[nodiscard]] constexpr std::string toString() const {

                return std::string(reinterpret_cast<const char*>(bytes.data()), getByteCount());
            }


            [[nodiscard]] constexpr bool operator==(const Utf8Char& character) const noexcept {

                return bytes == character.bytes;
            }

        private:

            std::array<u8, 4> bytes { 0 };
    };


    [[nodiscard]] inline constexpr Utf8Char operator ""_u8(const char* str, std::size_t) {

        return Utf8Char(str);
    }
}
