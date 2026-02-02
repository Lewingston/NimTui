
#include <gtest/gtest.h>

#include "Common/Utf8Char.h"

using namespace ImTui;


TEST(Utf8Char, GetByteCount) {

    { // one byte
        EXPECT_EQ(Utf8Char::getByteCount(0), 1);
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
    }
}


TEST(Utf8Char, ConstructFromString) {

    { // Test ASCII character

        Utf8Char utf8Char("a");

        // Check number of utf8 bytes
        EXPECT_EQ(utf8Char.getByteCount(), 1);

        // Check every single byte
        EXPECT_EQ(utf8Char.getBytes().at(0), 'a');
        EXPECT_EQ(utf8Char.getBytes().at(1), 0);
        EXPECT_EQ(utf8Char.getBytes().at(2), 0);
        EXPECT_EQ(utf8Char.getBytes().at(3), 0);

        // Check conversion back to string
        EXPECT_EQ(utf8Char.toString(), "a");

        std::cout << "LOL: " << utf8Char.toString() << '\n';
    }

    { // Test Umlaut

        Utf8Char utf8Char("ü");

        // Check number of utf8 bytes
        EXPECT_EQ(utf8Char.getByteCount(), 2);

        // Check every single byte
        EXPECT_EQ(utf8Char.getBytes().at(0), 0xc3);
        EXPECT_EQ(utf8Char.getBytes().at(1), 0xbc);
        EXPECT_EQ(utf8Char.getBytes().at(2), 0x00);
        EXPECT_EQ(utf8Char.getBytes().at(3), 0x00);

        // Check conversion back to string
        EXPECT_EQ(utf8Char.toString(), "ü");

        std::cout << "LEL: " <<  utf8Char.toString() << '\n';
    }

    { // Test emoji

        Utf8Char utf8Char("😉");

        // Check number of utf8 bytes
        EXPECT_EQ(utf8Char.getByteCount(), 4);

        // Check every single byte
        EXPECT_EQ(utf8Char.getBytes().at(0), 0xf0);
        EXPECT_EQ(utf8Char.getBytes().at(1), 0x9f);
        EXPECT_EQ(utf8Char.getBytes().at(2), 0x98);
        EXPECT_EQ(utf8Char.getBytes().at(3), 0x89);

        // Check conversion back to string
        EXPECT_EQ(utf8Char.toString(), "😉");
    }
}
