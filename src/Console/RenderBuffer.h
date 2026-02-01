#pragma once

#include "Color.h"
#include "Vec.h"

#include <vector>
#include <string>

namespace TUI {

    class RenderBuffer {

        public:

            struct CharData
            {
                std::string character  = " ";
                Color       frontColor = Color::BLACK;
                Color       backColor  = Color::WHITE;

                [[nodiscard]] bool operator==(const CharData& data) {

                    return character  == data.character &&
                           frontColor == data.frontColor &&
                           backColor  == data.backColor;
                }
            };

            RenderBuffer(Vec2<u32> size);

            virtual ~RenderBuffer() = default;

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
