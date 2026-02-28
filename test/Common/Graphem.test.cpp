
#include <gtest/gtest.h>

#include "Common/Grapheme.h"


using namespace TUI;


TEST(Grapheme, DefaultConstructor) {

    const Grapheme g;

    EXPECT_FALSE(g.isFullWidth());
    EXPECT_EQ(g.getStr(), "");
    EXPECT_EQ(g.getByteCount(), 0);
}


TEST(Grapheme, StringConstructor) {

    {
        const std::string str = "ABC";
        const Grapheme g(str);

        EXPECT_FALSE(g.isFullWidth());
        EXPECT_EQ(g.getStr(), "A");
        EXPECT_EQ(g.getByteCount(), 1);
    }

    {
        const std::string str = "ÄÖÜ";
        const Grapheme g(str);

        EXPECT_FALSE(g.isFullWidth());
        EXPECT_EQ(g.getStr(), "Ä");
        EXPECT_EQ(g.getByteCount(), 2);
    }

    {
        const std::string str = "😀😋😖";
        const Grapheme g(str);

        EXPECT_TRUE(g.isFullWidth());
        EXPECT_EQ(g.getStr(), "😀");
        EXPECT_EQ(g.getByteCount(), 4);
    }

    {
        const std::string str = "☢️☣️12345";
        const Grapheme g(str);

        EXPECT_TRUE(g.isFullWidth());
        EXPECT_EQ(g.getStr(), "☢️");
        EXPECT_EQ(g.getByteCount(), 6);
    }
}


TEST(Grapheme, CharPointerConstructor) {

    {
        const char* str = "ABC";
        const Grapheme g(str);

        EXPECT_FALSE(g.isFullWidth());
        EXPECT_EQ(g.getStr(), "A");
        EXPECT_EQ(g.getByteCount(), 1);
    }
}


TEST(Grapheme, ConstructionFromStringLiteral) {

    {
        const Grapheme g(" ");
        EXPECT_FALSE(g.isFullWidth());
        EXPECT_EQ(g.getStr(), " ");
        EXPECT_EQ(g.getByteCount(), 1);
    }
}


TEST(Grapheme, CreateVectorOfGraphemes) {

    const std::vector<Grapheme> vec(10);

    for (const auto& g : vec) {

        ASSERT_EQ(g.getStr(), "");
    }
}
