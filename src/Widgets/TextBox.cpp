
#include "TextBox.h"
#include "Primitives/Text.h"

#include <ranges>

using namespace TUI;


TextBox::TextBox(Vec2<s32> pos, Vec2<u32> size) :
    Widget(pos, size) {

}


void TextBox::draw(RenderBuffer& buffer, Vec2<s32> offset) {

    Widget::draw(buffer, offset);

    offset = offset + getPos();

    for (const std::string& line : textLines) {

        drawTextLine(buffer, offset, line);

        offset = offset + Vec2<s32>(0, 1);
    }
}


void TextBox::drawTextLine(RenderBuffer& buffer, Vec2<s32> offset, const std::string& line) {

    Text text(line.substr(0, getSize().getWidth()), offset);
    text.setFrontColor(textColor);
    text.setBackColor(getBackColor());

    text.draw(buffer);
}


void TextBox::setText(const std::string& text) {

    textLines.clear();

    for (auto&& line : std::views::split(text, '\n'))
        textLines.emplace_back(line.begin(), line.end());
}


std::string TextBox::getText() const {

    std::string text;

    for (std::size_t ii = 0; ii < textLines.size(); ii++) {

        text += textLines.at(ii);

        if (ii < textLines.size()- 1)
            text += '\n';
    }

    return text;
}
