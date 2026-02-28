
#include <gtest/gtest.h>

#include "Console/ConsoleString.h"

using namespace TUI;


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

    EXPECT_EQ(ConsoleString::getSubstring("😐❤️❤️😐", 2, 4), "❤️❤️");

    EXPECT_EQ(ConsoleString::getSubstring("☠️☠️❤️❤️❤️☠️☠️☠️", 4, 6), "❤️❤️❤️");

    EXPECT_EQ(ConsoleString::getSubstring("🏳️‍🌈🏳️‍🌈🏳️‍🌈", 1, 4), " 🏳️‍🌈 ");
}
