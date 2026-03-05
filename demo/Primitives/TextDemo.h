#pragma once

#include "../DemoPage.h"
#include "Widgets/Grid.h"
#include "Primitives/Text.h"

namespace TUI::Demo {

    class TextDemo : public DemoPage {

        public:

            TextDemo(Vec2<s32> pos, Vec2<u32> size);

            virtual ~TextDemo() = default;

            void setStyle(const Style& style) override;

            void draw(RenderBuffer& renderBuffer, Vec2<s32> offse) override;

        private:

            void setupGrid();

            [[nodiscard]] Text createText(Vec2<s32> pos,
                                          const std::string& str,
                                          Text::Align align) const;

            void onResize() override;

            static constexpr u32 gridX = 24;
            static constexpr u32 gridY = 12;

            Grid grid = Grid({0, 0}, getSize());

    };
}
