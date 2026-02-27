
#include <gtest/gtest.h>

#include "wtswidth.h"


TEST(Lib, wts8width) {

    { // ascii character normal width

        const std::string str = "A";

        EXPECT_EQ(wts8width(str.c_str(), str.length()), 1);
    }

    { // umlaut character noraml width

        const std::string str = "ü";

        EXPECT_EQ(wts8width(str.c_str(), str.length()), 1);
    }

    { // emoji character full width

        const std::string str = "😡";

        EXPECT_EQ(wts8width(str.c_str(), str.length()), 2);
    }

    {

        const std::string str = "☠️";

        EXPECT_EQ(wts8width(str.c_str(), str.length()), 2);
    }
}
