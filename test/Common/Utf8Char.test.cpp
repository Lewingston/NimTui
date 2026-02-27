
#include <gtest/gtest.h>

#include "Common/Utf8Char.h"

using namespace TUI;


TEST(Utf8Char, GetByteCount) {

    { // zero byte
        EXPECT_EQ(Utf8Char::getByteCount(0), 0);
    }

    { // one byte
        EXPECT_EQ(Utf8Char::getByteCount(0b0010'1111), 1);
    }

    { // two bytes
        EXPECT_EQ(Utf8Char::getByteCount(0b1100'0000), 2);
        EXPECT_EQ(Utf8Char::getByteCount(0b1101'0101), 2);
    }

    { // three bytes
        EXPECT_EQ(Utf8Char::getByteCount(0b1110'0000), 3);
        EXPECT_EQ(Utf8Char::getByteCount(0b1110'1111), 3);
    }

    { // four bytes
        EXPECT_EQ(Utf8Char::getByteCount(0b1111'0000), 4);
        EXPECT_EQ(Utf8Char::getByteCount(0b1111'0111), 4);
    }

    { // invalid
        EXPECT_GT(Utf8Char::getByteCount(0b1000'0000), 4);
        EXPECT_GT(Utf8Char::getByteCount(0b1111'1000), 4);
        EXPECT_GT(Utf8Char::getByteCount(0b1111'1111), 4);
    }

    {
        EXPECT_EQ(Utf8Char::getByteCount('a'), 1);
    }

    {
        const std::string t = "ä";
        EXPECT_EQ(Utf8Char::getByteCount(static_cast<u8>(t.at(0))), 2);
    }

    {
        const std::string t = "🙃";
        EXPECT_EQ(Utf8Char::getByteCount(static_cast<u8>(t.at(0))), 4);
    }

    {
        const std::string t = "💀";
        EXPECT_EQ(Utf8Char::getByteCount(static_cast<u8>(t.at(0))), 4);
    }
}


TEST(Utf8Char, CharacterDisplaySize) {

    { // Ascii character, normal width

        const Utf8Char utf8Char("d");
        EXPECT_FALSE(utf8Char.isFullWidth());
    }

    { // unlaut character, normal width

        const Utf8Char utf8Char("Ö");
        EXPECT_FALSE(utf8Char.isFullWidth());
    }

    { // emoji character, full width

        const Utf8Char utf8Char("😜");
        EXPECT_TRUE(utf8Char.isFullWidth());
    }
}


TEST(Utf8Char, DefaultConstructor) {

    // Test heap allocation for test coverage
    auto utf8Char = std::make_unique<Utf8Char>();

    EXPECT_EQ(utf8Char->getByteCount(), 0);

    EXPECT_EQ(utf8Char->getBytes().at(0), 0);
    EXPECT_EQ(utf8Char->getBytes().at(1), 0);
    EXPECT_EQ(utf8Char->getBytes().at(2), 0);
    EXPECT_EQ(utf8Char->getBytes().at(3), 0);

    EXPECT_EQ(utf8Char->toString(), "");
}


TEST(Utf8Char, ConstructFromCharPtr) {

    { // Test ASCII character

        const Utf8Char utf8Char("a");

        // Check number of utf8 bytes
        EXPECT_EQ(utf8Char.getByteCount(), 1);

        // Check every single byte
        EXPECT_EQ(utf8Char.getBytes().at(0), 'a');
        EXPECT_EQ(utf8Char.getBytes().at(1), 0);
        EXPECT_EQ(utf8Char.getBytes().at(2), 0);
        EXPECT_EQ(utf8Char.getBytes().at(3), 0);

        // Check conversion to string
        EXPECT_EQ(utf8Char.toString(), "a");
    }

    { // Test Umlaut

        const Utf8Char utf8Char("ü");

        // Check number of utf8 bytes
        EXPECT_EQ(utf8Char.getByteCount(), 2);

        // Check every single byte
        EXPECT_EQ(utf8Char.getBytes().at(0), 0xc3);
        EXPECT_EQ(utf8Char.getBytes().at(1), 0xbc);
        EXPECT_EQ(utf8Char.getBytes().at(2), 0x00);
        EXPECT_EQ(utf8Char.getBytes().at(3), 0x00);

        // Check conversion to string
        EXPECT_EQ(utf8Char.toString(), "ü");
    }

    { // Test emoji

        const Utf8Char utf8Char("😉");

        // Check number of utf8 bytes
        EXPECT_EQ(utf8Char.getByteCount(), 4);

        // Check every single byte
        EXPECT_EQ(utf8Char.getBytes().at(0), 0xf0);
        EXPECT_EQ(utf8Char.getBytes().at(1), 0x9f);
        EXPECT_EQ(utf8Char.getBytes().at(2), 0x98);
        EXPECT_EQ(utf8Char.getBytes().at(3), 0x89);

        // Check conversion to string
        EXPECT_EQ(utf8Char.toString(), "😉");
    }

    { // Test empty string

        const Utf8Char utf8Char("");

        // Check number of utf8 bytes
        EXPECT_EQ(utf8Char.getByteCount(), 0);

        // Check every single byte
        EXPECT_EQ(utf8Char.getBytes().at(0), 0);
        EXPECT_EQ(utf8Char.getBytes().at(1), 0);
        EXPECT_EQ(utf8Char.getBytes().at(2), 0);
        EXPECT_EQ(utf8Char.getBytes().at(3), 0);

        // Check conversion to string
        EXPECT_EQ(utf8Char.toString(), "");
    }

    { // Test construction from invalid utf8 string

        // Do not use constexpr for better code coverage results!
        const char str[] = { static_cast<char>(0b1111'1111), 0, 0, 0 };
        const Utf8Char utf8Char(str);

        // Check number of bytes
        EXPECT_EQ(utf8Char.getByteCount(), 0);

        // Check every single byte
        EXPECT_EQ(utf8Char.getBytes().at(0), 0);
        EXPECT_EQ(utf8Char.getBytes().at(1), 0);
        EXPECT_EQ(utf8Char.getBytes().at(2), 0);
        EXPECT_EQ(utf8Char.getBytes().at(3), 0);

        // Check conversion to string
        EXPECT_EQ(utf8Char.toString(), "");
    }
}


TEST(Utf8Char, EqualsOperator) {

    { // Should be equal
        Utf8Char char1("Ä");
        Utf8Char char2("Ä");

        EXPECT_TRUE(char1 == char2);
    }

    { // Should not be equal
        Utf8Char char1("Ä");
        Utf8Char char2("Ü");

        EXPECT_FALSE(char1 == char2);
    }
}


TEST(Utf8Char, ConstructFromLiteral) {

    { // normal construction

        const Utf8Char utf8Char = "Z"_u8;

        EXPECT_EQ(utf8Char.getByteCount(), 1);
        EXPECT_EQ(utf8Char.toString(), "Z");
    }

    { // construction from empty string

        const Utf8Char utf8Char = ""_u8;

        EXPECT_EQ(utf8Char.getByteCount(), 0);
        EXPECT_EQ(utf8Char.toString(), "");
    }

    { // Test literal function with string of size 0

        const char* test = "";
        const Utf8Char utf8Char = operator ""_u8(test, 0);

        EXPECT_EQ(utf8Char.getByteCount(), 0);
        EXPECT_EQ(utf8Char.toString(), "");
    }
}
