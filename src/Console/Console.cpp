
#include "Console.h"
#include "ConsoleSequences.h"

#include <stdexcept>
#include <iostream>

using namespace TUI;


Console::Console() {

    // Set code page to utf8
    SetConsoleOutputCP(CP_UTF8);

    outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    inputHandle = GetStdHandle(STD_INPUT_HANDLE);
}


Console::~Console() {

    leaveAlternateMode();
    showCursor();
}


Vec2<u32> Console::readConsoleSize() const {

    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    if (!GetConsoleScreenBufferInfo(outputHandle, &bufferInfo))
        throw std::runtime_error("Failed to get console information");

    const s32 width  = bufferInfo.srWindow.Right  - bufferInfo.srWindow.Left + 1;
    const s32 height = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top  + 1;

    return Vec2<u32>(static_cast<u32>(width), static_cast<u32>(height));
}


void Console::enterAlternateMode() {

    std::cout << ConsoleSequences::enterAlternateMode();
}


void Console::leaveAlternateMode() {

    std::cout << ConsoleSequences::leaveAlternateMode();
}


void Console::enableConsoleWindowInputEvents() {

    DWORD mode;
    GetConsoleMode(inputHandle, &mode);
    SetConsoleMode(inputHandle, mode | ENABLE_WINDOW_INPUT);
}


std::optional<Console::InputEvent> Console::readConsoleInput() const {

    INPUT_RECORD inputRecord;
    DWORD count;
    ReadConsoleInput(inputHandle, &inputRecord, 1, &count);

    if (count > 0) {

        return InputEvent(inputRecord);

    } else {

        return {};
    }
}


void Console::showCursor() {

    std::cout << ConsoleSequences::showCursor();
}


void Console::hideCursor() {

    std::cout << ConsoleSequences::hideCursor();
}


/************************************************************************/
/*                    struct Console::ResizeEvent                       */
/************************************************************************/


Console::KeyEvent::KeyEvent(const KEY_EVENT_RECORD& keyEventRecord) :
    pressed(keyEventRecord.bKeyDown),
    keyCode(static_cast<KeyCode>(keyEventRecord.wVirtualKeyCode)),
    keyModifiers(static_cast<KeyModifier>(keyEventRecord.dwControlKeyState)),
    asciiChar(keyEventRecord.uChar.AsciiChar){

}


/************************************************************************/
/*                    struct Console::ResizeEvent                       */
/************************************************************************/


Console::ResizeEvent::ResizeEvent(const WINDOW_BUFFER_SIZE_RECORD& bufferSizeRecord) :
    size(static_cast<u32>(bufferSizeRecord.dwSize.X),
         static_cast<u32>(bufferSizeRecord.dwSize.Y)) {

}


/************************************************************************/
/*                    struct Console::InputEvent                        */
/************************************************************************/


Console::InputEvent::InputEvent(const INPUT_RECORD& inputRecord) {

    switch (inputRecord.EventType) {

        case FOCUS_EVENT:
            break;
        case KEY_EVENT:
            event = KeyEvent(inputRecord.Event.KeyEvent);
            break;
        case MENU_EVENT:
        case MOUSE_EVENT:
            break;
        case WINDOW_BUFFER_SIZE_EVENT:
            event = ResizeEvent(inputRecord.Event.WindowBufferSizeEvent);
            break;
        default:
            break;
    }
}
