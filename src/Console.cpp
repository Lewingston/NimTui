
/*
#include "Console.h"

#include <stdexcept>
#include <iostream>

#include <windows.h>

using namespace TUI;


Vec2<u32> Console::getSize() {

    const HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    if (!GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo)) {
        throw std::runtime_error("Failed to get console information!");
    }

    const s32 width  = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1;
    const s32 height = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1;

    return Vec2<u32>(static_cast<u32>(width), static_cast<u32>(height));
}


void Console::enterAlternateMode() {

    std::cout << "\x1b[?1049h";
}


void Console::leaveAlternateMode() {

    std::cout << "\x1b[?1049l";
}


void Console::hideCursor() {

    std::cout << "\x1b[?25l";
}
*/
