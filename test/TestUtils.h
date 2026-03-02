#pragma once

#include <gtest/gtest.h>

#include "Console/RenderBuffer.h"

namespace TUI {

    class TestUtils {

        public:

            using CharData = RenderBuffer::CharData;

            [[nodiscard]] static bool CompareCharData(const CharData& c1, const CharData& c2) {

                EXPECT_EQ(c1.grapheme.getStr(), c2.grapheme.getStr());
                EXPECT_EQ(c1.frontColor, c2.frontColor);
                EXPECT_EQ(c1.backColor,  c2.backColor);

                return c1 == c2;
            }
    };
}
