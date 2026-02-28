
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

            ASSERT_EQ(data.grapheme, " ") << " X: " << x << " Y: " << y;
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
    ASSERT_EQ(data.grapheme, "A");
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

            ASSERT_EQ(data.grapheme, " ") << " X: " << x << " Y: " << y;
            ASSERT_EQ(data.frontColor, Color::BLACK);
            ASSERT_EQ(data.backColor, Color::WHITE);
        }
    }
}


TEST(RenderBuffer, GetDataFromInvalidPosition) {

    RenderBuffer buffer({4, 4});

    // change every character in the buffer
    for (u32 x = 0; x < buffer.getSize().getX(); x++) {
        for (u32 y = 0; y < buffer.getSize().getY(); y++) {

            buffer.set({x, y}, {"X", Color::GREEN, Color::RED});
        }
    }

    const RenderBuffer::CharData& data = buffer.get({0, 4});

    const RenderBuffer::CharData defaultData;

    ASSERT_EQ(data, defaultData);
}


TEST(RenderBuffer, CreateTerminalSequence) {

    RenderBuffer buffer({2, 1});
    buffer.set({0, 0}, {"a", Color::RED, Color::BLUE});
    buffer.set({1, 0}, {"b", Color::RED, Color::BLUE});

    {
        const std::string seq = buffer.createTerminalSequence();

        const std::string refSeq =
            "\x1b[0;0H"          // Move cursor to position 0, 0
            "\x1b[38;2;255;0;0m" // Set front color to red
            "\x1b[48;2;0;0;255m" // Set back color to blue
            "a"                  // Print first character
            "b";                 // Print second character

        ASSERT_EQ(seq, refSeq);
    }

    { // when generating the sequence a second time, nothing should be
      // put on the console, because no characters where changed

        const std::string seq = buffer.createTerminalSequence();

        ASSERT_EQ(seq, "");
    }

    { // Test sequqnce generation on render buffer of size 0

        RenderBuffer buffer({0, 0});
        const std::string seq = buffer.createTerminalSequence();
        ASSERT_EQ(seq, "");
    }
}


TEST(RenderBuffer, CreateTermianlSequqnceFullWidthChar) {

    RenderBuffer buffer({2, 1});
    buffer.set({0, 0}, {"😠", Color::WHITE, Color::BLACK});
    buffer.set({1, 0}, {"x",  Color::WHITE, Color::BLACK});

    {
        const std::string seq = buffer.createTerminalSequence();

        const std::string refSeq =
            "\x1b[0;0H"              // Move cursor to position 0, 0
            "\x1b[38;2;255;255;255m" // Set front color to white
            "\x1b[48;2;0;0;0m"       // Set back color to black
            "😠";                    // print first character

        ASSERT_EQ(seq, refSeq);
    }

    { // second sequqnce generation should be empty, all characters are clean

        const std::string seq = buffer.createTerminalSequence();

        ASSERT_EQ(seq, "");
    }
}


TEST(RenderBufferCharData, EqualOperator) {

    using CharData = RenderBuffer::CharData;

    { // Should be equal
        const CharData data1{"a", Color::RED, Color::WHITE};
        const CharData data2{"a", Color::RED, Color::WHITE};

        EXPECT_TRUE(data1 == data2);
    }

    { // Different character
        const CharData data1{"a", Color::GREEN, Color::GREEN};
        const CharData data2{"b", Color::GREEN, Color::GREEN};

        EXPECT_FALSE(data1 == data2);
    }

    { // Different front color
        const CharData data1("a", Color::RED, Color::WHITE);
        const CharData data2("a", Color::BLUE, Color::WHITE);

        EXPECT_FALSE(data1 == data2);
    }

    { // Different back color
        const CharData data1("a", Color::RED, Color::WHITE);
        const CharData data2("a", Color::RED, Color::BLACK);

        EXPECT_FALSE(data1 == data2);
    }
}
