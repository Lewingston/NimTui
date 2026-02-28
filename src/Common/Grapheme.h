#pragma once

#include "Unicode.h"

#include <string>

namespace TUI {

    class Grapheme final {

        public:

            using Info = Unicode::Info;

            Grapheme() = default;

            Grapheme(const std::string& str) :
                Grapheme(str, Unicode::getInfo(str)) {}

            Grapheme(const char* str) :
                Grapheme(std::string(str)) {}

            [[nodiscard]] bool isFullWidth() const noexcept { return fullWidth; }

            [[nodiscard]] std::size_t getByteCount() const noexcept { return str.length(); }

            [[nodiscard]] const std::string& getStr() const noexcept { return str; }

            [[nodiscard]] bool operator==(const Grapheme& g) const {

                return str == g.str;
            }

        private:

            Grapheme(const std::string& str, Info info) :
                str(str.substr(0, info.byteCount)),
                fullWidth(info.width >= 2) { }

            std::string str{};

            bool fullWidth = false;
    };
}
