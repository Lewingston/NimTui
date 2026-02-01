
#include <gtest/gtest.h>

#include "Console/RenderBuffer.h"

using namespace TUI;


TEST(RenderBuffer, Constructor) {

    const u32 width = 5;
    const u32 height = 8;

    RenderBuffer buffer({width, height});

    ASSERT_EQ(buffer.getSize().getX(), width);
    ASSERT_EQ(buffer.getSize().getY(), height);

    for (u32 x = 0; x < width; x++) {
        for (u32 y = 0; y < height; y++) {

            const RenderBuffer::CharData& data = buffer.get({x, y});

            ASSERT_EQ(data.character, " ");
            ASSERT_EQ(data.frontColor, Color::BLACK);
            ASSERT_EQ(data.backColor, Color::WHITE);
        }
    }
}


TEST(RenderBuffer, SetData) {

    RenderBuffer buffer({4, 4});

    buffer.set({2, 3}, {"A", Color::RED, Color::BLUE});

    const RenderBuffer::CharData& data = buffer.get({2, 3});

    // Check if character was correcty set
    ASSERT_EQ(data.character, "A");
    ASSERT_EQ(data.frontColor, Color::RED);
    ASSERT_EQ(data.backColor, Color::BLUE);

    // Try to set character outside the buffer
    buffer.set({4, 0}, {"B", Color::GREEN, Color::RED});

    // Check if all other characters are unmodified
    for (u32 x = 0; x < 4; x++) {
        for (u32 y = 0; y < 4; y++) {

            if (x == 2 && y == 3) // skip the modied character
                continue;

            const RenderBuffer::CharData& data = buffer.get({x, y});

            ASSERT_EQ(data.character, " ");
            ASSERT_EQ(data.frontColor, Color::BLACK);
            ASSERT_EQ(data.backColor, Color::WHITE);
        }
    }
}


TEST(RenderBuffer, GetDataFromInvalidPosition) {

    const RenderBuffer buffer({4, 4});
}
