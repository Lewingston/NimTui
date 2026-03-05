#pragma once

#include "../DemoPage.h"
#include "Widgets/Grid.h"

namespace TUI::Demo {

    class RectDemo : public DemoPage {

        public:

            RectDemo(Vec2<s32> pos, Vec2<u32> size);

            virtual ~RectDemo() = default;

            void setStyle(const Style& style) override;

            void draw(RenderBuffer& renderBuffer, Vec2<s32> offset) override;

        private:

            void setupGrid();

            void onResize() override;

            Grid grid = Grid({0, 0}, getSize());
    };
}
