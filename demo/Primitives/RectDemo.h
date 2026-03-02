#pragma once

#include "../DemoPage.h"
#include "Widgets/Grid.h"

namespace TUI {

    class RectDemo : public DemoPage {

        public:

            RectDemo(Vec2<s32> pos, Vec2<u32> size);

            virtual ~RectDemo() = default;

            void draw(RenderBuffer& renderBuffer, Vec2<s32> offset) override;

            void onResize(Vec2<u32> oldSize, Vec2<u32> newSize) override;

        private:

            void setupGrid();

            Grid grid = Grid({0, 0}, getSize());
    };
}
