
#include <gtest/gtest.h>

#include "Console/ConsoleSequences.h"

using namespace TUI;


TEST(ConsoleSequences, SequencesWithoutParameters) {

    constexpr std::string_view enterAlternateMode = ConsoleSequences::enterAlternateMode();
    EXPECT_EQ(enterAlternateMode, "\x1b[?1049h");

    constexpr std::string_view leaveAlternateMode = ConsoleSequences::leaveAlternateMode();
    EXPECT_EQ(leaveAlternateMode, "\x1b[?1049l");

    constexpr std::string_view showCursor = ConsoleSequences::showCursor();
    EXPECT_EQ(showCursor, "\x1b[?25h");

    constexpr std::string_view hideCursor = ConsoleSequences::hideCursor();
    EXPECT_EQ(hideCursor, "\x1b[?25l");

    constexpr std::string_view resetTextFormat = ConsoleSequences::resetTextFormat();
    EXPECT_EQ(resetTextFormat, "\x1b[0m");
}


TEST(ConsoleSequences, SequencesWithParameters) {

    const std::string setCursorPos = ConsoleSequences::setCursorPos(37, 49);
    EXPECT_EQ(setCursorPos, "\x1b[49;37H");

    const std::string setFrontColor = ConsoleSequences::setFrontColor({33, 66, 99});
    EXPECT_EQ(setFrontColor, "\x1b[38;2;33;66;99m");

    const std::string setBackColor = ConsoleSequences::setBackColor({99, 66, 33});
    EXPECT_EQ(setBackColor, "\x1b[48;2;99;66;33m");
}
