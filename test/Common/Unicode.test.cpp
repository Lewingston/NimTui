
#include <gtest/gtest.h>

#include "Common/Unicode.h"

using namespace TUI;


TEST(Unicode, GetInfoFromString) {

    { // Empty string

        EXPECT_EQ(Unicode::getInfo(""), Unicode::Info(0, 0));
    }

    { // ASCII character normal width

        EXPECT_EQ(Unicode::getInfo("A"), Unicode::Info(1, 1));
    }

    { // Multiple ASCII characters (only first one should be checked)

        EXPECT_EQ(Unicode::getInfo("BCDEF"), Unicode::Info(1, 1));
    }

    { // Umlaut character noraml width

        EXPECT_EQ(Unicode::getInfo("ö"), Unicode::Info(2, 1));
    }

    { // Multiple umlauch characters (only first one should be checked)

        EXPECT_EQ(Unicode::getInfo("ÄÖÜ"), Unicode::Info(2, 1));
    }

    { // Mixed ASCII and umlaut characters, ASCII first

        EXPECT_EQ(Unicode::getInfo("aääbüa"), Unicode::Info(1, 1));
    }

    { // Mixed ACII and umlaut characters, umalut first

        EXPECT_EQ(Unicode::getInfo("äaüuöo"), Unicode::Info(2, 1));
    }

    { // Emoji character, single code point, full width

        EXPECT_EQ(Unicode::getInfo("😡"), Unicode::Info(4, 2));
    }

    { // Emoji character, full width, 2 multiple code points

        EXPECT_EQ(Unicode::getInfo("☠️"), Unicode::Info(6 ,2));
    }

    { // Emoji character, full width, 4 code points

        EXPECT_EQ(Unicode::getInfo("🏳️‍🌈"), Unicode::Info(14, 2));
    }
}


TEST(Unicode, GetInfoFromStringWithOffset) {

    { // ASCII string

        EXPECT_EQ(Unicode::getInfo("12345678", 4), Unicode::Info(1, 1));
    }

    { // String with umlaute

        const std::string str = "123äüö456😀🤔x😵‍💫ß";

        const std::vector<std::string> ref =
            { "1", "2", "3", "ä", "ü", "ö", "4", "5", "6",
              "😀", "🤔", "x", "😵‍💫", "ß"};
        u32 refIndex = 0;

        for (std::size_t ii = 0; ii < str.length();) {

            const auto info = Unicode::getInfo(str, ii);

            ASSERT_EQ(str.substr(ii, info.byteCount), ref.at(refIndex)) << " Index: " << refIndex;

            refIndex += 1;
            ii += info.byteCount;
        }
    }
}
