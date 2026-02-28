#pragma once

#include "Types.h"

#include <string>

namespace TUI {

    class Unicode final {

        public:

            struct Info {

                u8 byteCount = 0;
                u8 width     = 0;

                [[nodiscard]] bool operator==(const Info info) const noexcept {

                    return width == info.width && byteCount == info.byteCount;
                }
            };

            Unicode() = delete;
            ~Unicode() = delete;

            /*
             * Returns the number of bytes of the first graphem in the string
             * and the number of character blocks the graphem takes in the console.
             * 1 for normal characters
             * 2 for full width characters
             * Returns 0 width and 0 byte count in case of an encoding error
             */
            [[nodiscard]] static Info getInfo(const std::string& str) noexcept;

            /*
             * Returns the unicode grapheme information for the character in the string
             * Starting from the byte with the number "offset".
             */
            [[nodiscard]] static Info getInfo(const std::string& str, std::size_t offset) noexcept;

            /*
             * Same as the GetInfo(const std::string&) function. Takes a char pointer
             * and string length as parameter. String must no be null terminated.
             */
            [[nodiscard]] static Info getInfo(const char* str, std::size_t len) noexcept;

    };
}
