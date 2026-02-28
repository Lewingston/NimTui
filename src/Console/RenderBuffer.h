#pragma once

#include "Color.h"
#include "Vec.h"
#include "Grapheme.h"

#include <vector>
#include <string>

namespace TUI {

    class RenderBuffer final {

        public:

            struct CharData
            {
                Grapheme grapheme {" "};
                Color    frontColor = Color::BLACK;
                Color    backColor  = Color::WHITE;

                [[nodiscard]] constexpr bool operator==(const CharData& data) const noexcept {

                    return grapheme   == data.grapheme   &&
                           frontColor == data.frontColor &&
                           backColor  == data.backColor;
                }
            };

            RenderBuffer(Vec2<u32> size);

            void set(Vec2<u32> pos, const CharData& charData);
            [[nodiscard]] const CharData& get(Vec2<u32> pos) const;

            [[nodiscard]] const Vec2<u32>& getSize() const noexcept { return size; }

            std::string createTerminalSequence();

        private:

            std::size_t posToIndex(Vec2<u32> pos) const noexcept;

            Vec2<u32> size;

            std::vector<CharData> characters;
            std::vector<bool> dirty;

    };
}
