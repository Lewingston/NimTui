
#include <gtest/gtest.h>

#include "Widgets/Widget.h"
#include "Console/RenderBuffer.h"

using namespace TUI;


TEST(Widget, Constructor) {

    Widget widget({2, 4}, {7, 9});

    ASSERT_EQ(widget.getSize().getWidth(), 7);
    ASSERT_EQ(widget.getSize().getHeight(), 9);
    ASSERT_EQ(widget.getPos().getX(), 2);
    ASSERT_EQ(widget.getPos().getY(), 4);

    ASSERT_EQ(widget.getBackColor(), Color::BLACK);
}


TEST(Widget, Destructor) {

    Widget* widget = new Widget({0, 0}, {0, 0});
    delete widget;
}


TEST(Widget, backColor) {

    Widget widget({2, 2}, {4, 4});

    Color color(56, 133, 99);
    widget.setBackColor(color);

    EXPECT_EQ(widget.getBackColor(), color);
}


TEST(Widget, size) {

    Widget widget({0, 0}, {6, 7});

    EXPECT_EQ(widget.getSize().getWidth(), 6);
    EXPECT_EQ(widget.getSize().getHeight(), 7);

    widget.setSize({11, 12});

    EXPECT_EQ(widget.getSize().getWidth(), 11);
    EXPECT_EQ(widget.getSize().getHeight(), 12);
}


TEST(Widget, position) {

    Widget widget({3, 4}, {12, 12});

    EXPECT_EQ(widget.getPos().getX(), 3);
    EXPECT_EQ(widget.getPos().getY(), 4);

    widget.setPos({7, 9});

    EXPECT_EQ(widget.getPos().getX(), 7);
    EXPECT_EQ(widget.getPos().getY(), 9);
}


TEST(Widget, draw) {

    const Color g = Color::GREEN;
    const Color w = Color::WHITE;

    { // draw without offset

        constexpr u8 bufferWidth  = 6;
        constexpr u8 bufferHeight = 6;

        RenderBuffer buffer({bufferWidth, bufferHeight});
        Widget widget({1, 1}, {4, 4});
        widget.setBackColor(g);

        widget.draw(buffer, {0, 0});

        const std::array<std::array<Color, bufferWidth>, bufferHeight> ref =
        {{
            {w, w, w, w, w, w},
            {w, g, g, g, g, w},
            {w, g, g, g, g, w},
            {w, g, g, g, g, w},
            {w, g, g, g, g, w},
            {w, w, w, w, w, w}
        }};

        for (u8 y = 0; y < buffer.getSize().getHeight(); y++) {
            for (u8 x = 0; x < buffer.getSize().getWidth(); x++) {

                const Color bc = buffer.get({x, y}).backColor;
                const Color rc = ref[y][x];
                ASSERT_EQ(bc, rc);
            }
        }
    }

    { // draw with offset

        constexpr u8 bufferWidth  = 7;
        constexpr u8 bufferHeight = 8;

        RenderBuffer buffer({bufferWidth, bufferHeight});
        Widget widget({1, 1}, {4, 4});
        widget.setBackColor(g);

        widget.draw(buffer, {1, 2});

        const std::array<std::array<Color, bufferWidth>, bufferHeight> ref =
        {{
            {w, w, w, w, w, w, w},
            {w, w, w, w, w, w, w},
            {w, w, w, w, w, w, w},
            {w, w, g, g, g, g, w},
            {w, w, g, g, g, g, w},
            {w, w, g, g, g, g, w},
            {w, w, g, g, g, g, w},
            {w, w, w, w, w, w, w}
        }};

        for (u8 y = 0; y < buffer.getSize().getHeight(); y++) {
            for (u8 x = 0; x < buffer.getSize().getWidth(); x++) {

                const Color bc = buffer.get({x, y}).backColor;
                const Color rc = ref[y][x];
                ASSERT_EQ(bc, rc);
            }
        }
    }
}
