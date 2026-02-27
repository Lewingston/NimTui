
#include <gtest/gtest.h>

#include "Console/ConsoleString.h"

using namespace TUI;


TEST(ConsoleString, GetByteCountForConsoleSize) {

    EXPECT_EQ(ConsoleString::getByteCountForConsoleSize("TestString", 4), 4);

    EXPECT_EQ(ConsoleString::getByteCountForConsoleSize("blabla", 8), 6);

    EXPECT_EQ(ConsoleString::getByteCountForConsoleSize("123456", 6), 6);

    EXPECT_EQ(ConsoleString::getByteCountForConsoleSize("123456", 5), 5);

    EXPECT_EQ(ConsoleString::getByteCountForConsoleSize("1234Ü", 20), 6);

    EXPECT_EQ(ConsoleString::getByteCountForConsoleSize("12ö56ä89", 4), 5);

    EXPECT_EQ(ConsoleString::getByteCountForConsoleSize("äöüäöü", 6), 12);

    EXPECT_EQ(ConsoleString::getByteCountForConsoleSize("äöüäö", 5), 10);

    EXPECT_EQ(ConsoleString::getByteCountForConsoleSize("123😁456", 8), 10);

    EXPECT_EQ(ConsoleString::getByteCountForConsoleSize("🧐🤓😎🥸", 4), 8);

    EXPECT_EQ(ConsoleString::getByteCountForConsoleSize("🧐🤓😎🥸", 3), 8);
}


TEST(ConsoleString, GetSubstring) {

    EXPECT_EQ(ConsoleString::getSubstring("ABCD", 0, 4), "ABCD");

    EXPECT_EQ(ConsoleString::getSubstring("ABCDEFGHIJKLMNOP", 4, 6), "EFGHIJ");

    EXPECT_EQ(ConsoleString::getSubstring("ABCDE", 2, 2), "CD");

    EXPECT_EQ(ConsoleString::getSubstring("1234567890", 6, 10), "7890");

    EXPECT_EQ(ConsoleString::getSubstring("1234", 6, 6), "");

    EXPECT_EQ(ConsoleString::getSubstring("123äöü789", 3, 3), "äöü");

    EXPECT_EQ(ConsoleString::getSubstring("äöüäöü", 0, 4), "äöüä");

    EXPECT_EQ(ConsoleString::getSubstring("123äöü", 2, 10), "3äöü");

    EXPECT_EQ(ConsoleString::getSubstring("123🙃678", 2, 4), "3🙃6");

    EXPECT_EQ(ConsoleString::getSubstring("🙃🙃🙃🙃", 2, 4), "🙃🙃");

    EXPECT_EQ(ConsoleString::getSubstring("💀🤡🤡💀", 1, 6), " 🤡🤡 ");

    EXPECT_EQ(ConsoleString::getSubstring("12😍😍💀💀7890", 0, 7), "12😍😍 ");

    EXPECT_EQ(ConsoleString::getSubstring("💀💀😍😍😍ABCDEFGH", 3, 9), " 😍😍😍AB");
}
