
#include <gtest/gtest.h>

#include "Widgets/Widget.h"

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
