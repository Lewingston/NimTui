
#include <gtest/gtest.h>

#include "Color.h"

using namespace TUI;


TEST(Color, Constructor) {

    Color color(33, 66, 99);

    EXPECT_EQ(color.getR(), 33);
    EXPECT_EQ(color.getG(), 66);
    EXPECT_EQ(color.getB(), 99);
}


TEST(Color, EqualOperator) {

    { // should be equal
        const Color color1(25, 50, 75);
        const Color color2(25, 50, 75);

        const bool equal = color1 == color2;

        EXPECT_TRUE(equal);
    }

    { // different red value
        const Color color1(25, 50, 75);
        const Color color2(75, 50, 75);

        const bool equal = color1 == color2;

        EXPECT_FALSE(equal);
    }

    { // different green value
        const Color color1(25, 33, 75);
        const Color color2(25, 66, 75);

        const bool equal = color1 == color2;

        EXPECT_FALSE(equal);
    }

    { // different blue value
        const Color color1(25, 50, 99);
        const Color color2(25, 50, 123);

        const bool equal = color1 == color2;

        EXPECT_FALSE(equal);
    }
}
