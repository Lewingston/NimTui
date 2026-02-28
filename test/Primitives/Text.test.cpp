
#include <gtest/gtest.h>

#include "Primitives/Text.h"
#include "Console/RenderBuffer.h"
#include "../TestUtils.h"

using namespace TUI;

using CharData = RenderBuffer::CharData;


TEST(Text, ASCII_Text) {

    Text text("abcdef", {0, 0});
    text.setFrontColor(Color::BLACK);
    text.setBackColor(Color::WHITE);

    RenderBuffer buffer({6, 1});

    text.draw(buffer);

    ASSERT_TRUE(CompareCharData(buffer.get({0, 0}), CharData("a")));
    ASSERT_TRUE(CompareCharData(buffer.get({1, 0}), CharData("b")));
    ASSERT_TRUE(CompareCharData(buffer.get({2, 0}), CharData("c")));
    ASSERT_TRUE(CompareCharData(buffer.get({3, 0}), CharData("d")));
    ASSERT_TRUE(CompareCharData(buffer.get({4, 0}), CharData("e")));
}


TEST(Text, Umlaute) {

    Text text("abüäöghi", {0, 0});
    text.setFrontColor(Color::BLACK);
    text.setBackColor(Color::WHITE);

    RenderBuffer buffer({7, 1});

    text.draw(buffer);

    ASSERT_TRUE(CompareCharData(buffer.get({0, 0}), CharData("a")));
    ASSERT_TRUE(CompareCharData(buffer.get({1, 0}), CharData("b")));
    ASSERT_TRUE(CompareCharData(buffer.get({2, 0}), CharData("ü")));
    ASSERT_TRUE(CompareCharData(buffer.get({3, 0}), CharData("ä")));
    ASSERT_TRUE(CompareCharData(buffer.get({4, 0}), CharData("ö")));
    ASSERT_TRUE(CompareCharData(buffer.get({5, 0}), CharData("g")));
    ASSERT_TRUE(CompareCharData(buffer.get({6, 0}), CharData("h")));
}


TEST(Text, Emojis) {

}
