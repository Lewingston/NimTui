
#include "ConsoleWindow.h"
#include "Console.h"

#include <stdexcept>

using namespace TUI;

/******************************************************************/
/*                      class ConsoleBuffer                       */
/******************************************************************/

/*
ConsoleBuffer::ConsoleBuffer() {

    bufferHandle = CreateConsoleScreenBuffer(
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        CONSOLE_TEXTMODE_BUFFER,
        nullptr
    );

    if (bufferHandle == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("Failed to create console buffer!");
    }

    newBuffer = true;
}


ConsoleBuffer::ConsoleBuffer(HANDLE bufferHandle) :
    bufferHandle(bufferHandle) { }


ConsoleBuffer::~ConsoleBuffer() {

    if (newBuffer)
        CloseHandle(bufferHandle);
}


void ConsoleBuffer::setActive() {

    SetConsoleActiveScreenBuffer(bufferHandle);
}


void ConsoleBuffer::write(const std::string& str) {

    DWORD charsWritten = 0;
    DWORD length = static_cast<DWORD>(str.length());

    WriteConsoleA(
        bufferHandle,
        str.c_str(),
        length,
        &charsWritten,
        nullptr
    );
}


void ConsoleBuffer::setCursorPos(u32 x, u32 y) {

    SetConsoleCursorPosition(
        bufferHandle,
        { static_cast<SHORT>(x), static_cast<SHORT>(y), }
    );
}
*/


/******************************************************************/
/*                       class RenderBuffer                       */
/******************************************************************/

/*
RenderBuffer::RenderBuffer(u32 width, u32 height) : RenderBuffer(Vec2<u32>(width, height)) { }


RenderBuffer::RenderBuffer(Vec2<u32> size) :
    size(size), characters(size.getX() * size.getY()) { }


void RenderBuffer::set(Vec2<u32> pos, std::string character, Color backColor, Color frontColor) {

    const u32 posIndex = pos.getY() * size.getWidth() + pos.getX();
    if (posIndex >= characters.size())
        return;

    characters.at(posIndex) = CharInfo {
        .character  = character,
        .backColor  = backColor,
        .frontColor = frontColor
    };
}


const RenderBuffer::CharInfo& RenderBuffer::get(Vec2<u32> pos) const {

    static const CharInfo invalid;

    const u32 posIndex = pos.getY() * size.getWidth() + pos.getX();
    if (posIndex >= characters.size())
        return invalid;

    return characters.at(posIndex);
}


void RenderBuffer::print(Vec2<s32> pos, std::string& text, Color color) {

    for (s32 ii = 0; ii < text.length(); ii++) {

        const s32 posX = pos.getX() + ii;
        const s32 posY = pos.getY();

        if (posX < 0 || posY < 0)
            continue;

        const Vec2<u32> currentPos(posX, posY);

        const Color backColor = get(currentPos).backColor;
        set(currentPos, std::string(1, text.at(ii)), backColor, color);
    }
}


void RenderBuffer::blit(ConsoleBuffer& console) {

    console.setCursorPos(0, 0);

    std::string str;

    for (const CharInfo& character : characters) {

        str += character.getTermSeq();
    }

    console.write(str);
}


std::string RenderBuffer::CharInfo::getTermSeq() const {

    std::string seq = "";

    seq += "\x1b[48;2;";
    seq += colorToString(backColor) + 'm';

    seq += "\x1b[38;2;";
    seq += colorToString(frontColor) + 'm';

    seq += character;

    return seq;
}


std::string RenderBuffer::CharInfo::colorToString(Color color) const {

    std::string str = std::to_string(color.getR()) + ";";
    str += std::to_string(color.getG()) + ";";
    str += std::to_string(color.getB());

    return str;
}
*/


/******************************************************************/
/*                      class ConsoleWindow                       */
/******************************************************************/

/*
ConsoleWindow::ConsoleWindow() {

    const Vec2<u32> size = Console::getSize();

    HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    stdBuffer = std::make_unique<ConsoleBuffer>(stdHandle);

    renderBuffer = std::make_unique<RenderBuffer>(size.getWidth(), size.getHeight());
}


RenderBuffer& ConsoleWindow::getRenderBuffer() {

    if (!renderBuffer)
        throw std::runtime_error("Render buffer does not exist!");

    return *renderBuffer;
}


void ConsoleWindow::show() {

    Console::enterAlternateMode();
    Console::hideCursor();
}


void ConsoleWindow::hide() {

    Console::leaveAlternateMode();
}


void ConsoleWindow::flip() {

    renderBuffer->blit(*stdBuffer);
}
*/
