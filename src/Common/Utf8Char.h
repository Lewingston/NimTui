#pragma once

#include "Types.h"

#include <array>
#include <string>
#include <limits>

namespace ImTui {

    class Utf8Char final {

        public:

            constexpr Utf8Char(const std::string& str) {

                if (str.empty())
                    return;

                const u8 count = getByteCount(static_cast<u8>(str.at(0)));

                for (u8 ii = 0; ii < count && ii < str.size(); ii++) {
                    bytes[ii] = static_cast<u8>(str.at(ii));
                }
            }


            [[nodiscard]] static constexpr u8 getByteCount(const u8 firstByte) noexcept {

                if ((firstByte & 0b1000'0000) == 0)
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

                const u8 size = getByteCount();
                if (size > 4)
                    return "";

                return std::string(reinterpret_cast<const char*>(bytes.data()), size);
            }

        private:

            std::array<u8, 4> bytes { 0 };
    };
}
