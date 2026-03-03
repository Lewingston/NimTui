
#include "TextDemo.h"

using namespace TUI;


TextDemo::TextDemo(Vec2<s32> pos, Vec2<u32> size) :
    DemoPage(pos, size)
{
    setupGrid();
}


void TextDemo::setStyle(const Style& style) {

    DemoPage::setStyle(style);
    grid.setColors(style.primaryBackColor, style.secondaryBackColor);
    grid.setTextColor(style.borderColor);
}


void TextDemo::onResize() {

    DemoPage::onResize();
    grid.setSize(getSize());
}


void TextDemo::setupGrid() {

    grid.setGridSize({gridX, gridY});
    grid.enableNumbers(true);
    grid.enableOffset(false);
};


Text TextDemo::createText(Vec2<s32> pos,
                          const std::string& str,
                          Text::Align align) const {

    Text text(str, pos, align);
    text.setFrontColor(getStyle().text.color);
    text.setBackColor(Color::BLACK);

    return text;
}


void TextDemo::draw(RenderBuffer& renderBuffer, Vec2<s32> offset) {

    grid.draw(renderBuffer, getPos() + offset);

    const Vec2<s32> size    = { static_cast<s32>(gridX) - 4, static_cast<s32>(gridY) - 2 };
    const Vec2<s32> offsetX = { static_cast<s32>(gridX), 0 };
    const Vec2<s32> offsetY = { 0, static_cast<s32>(gridY) };

    Vec2<s32> pos = {1, 1};

    {
        const Text t = createText(pos,
                                  "Text algin\ntop left\nmore text",
                                  Text::Align::TOP_LEFT);
        t.draw(renderBuffer);

        pos += offsetX;
    }

    {
        const Text t = createText(pos + Vec2<s32>((size.getX()) / 2, 0),
                                  "Text algin\ntop center\nadditional text line",
                                  Text::Align::TOP_CENTER);
        t.draw(renderBuffer);

        pos += offsetX;
    }

    {
        const Text t = createText(pos + Vec2<s32>(offsetX.getX() - 2, 0),
                                  "Text align\ntop right\na longer text line\nand one more line",
                                  Text::Align::TOP_RIGHT);
        t.draw(renderBuffer);

        pos += offsetX;
    }

    {
        Text t = createText(pos + Vec2<s32>(offsetX.getX() - 2, 0),
                            "Text in the\ntop right\nwith block\nalignment",
                            Text::Align::TOP_RIGHT);
        t.setBlockAlign(true);
        t.draw(renderBuffer);

        pos = Vec2<s32>{1, 1} + offsetY;
    }

    {
        const Text t = createText(pos + Vec2<s32>(0, size.getY() / 2),
                                  "Text aligned in\nthe middle\nand ot the left\nexample\nmore text",
                                  Text::Align::CENTER_LEFT);
        t.draw(renderBuffer);

        pos += offsetX;
    }

    {
        const Text t = createText(pos + size / 2,
                                  "Text aligned\nexactly in the\nmiddle of this\ngrid square",
                                  Text::Align::CENTER);
        t.draw(renderBuffer);

        pos += offsetX;
    }

    {
        const Text t = createText(pos + Vec2<s32>(offsetX.getX() - 2, size.getY() / 2),
                                  "Text aligned\nto the center\nright",
                                  Text::Align::CENTER_RIGHT);
        t.draw(renderBuffer);

        pos += offsetX;
    }

    {
        Text t = createText(pos + size / 2,
                            "Bloack align\nin the\ncenter",
                            Text::Align::CENTER);
        t.setBlockAlign(true);
        t.draw(renderBuffer);

        pos = Vec2<s32>(1, 1) + offsetY * 2;
    }

    {
        const Text t = createText(pos + Vec2<s32>(0, size.getY()),
                                  "Text\nin the bottom\nright corner",
                                  Text::Align::BOTTOM_LEFT);
        t.draw(renderBuffer);

        pos += offsetX;
    }

    {
        const Text t = createText(pos + Vec2<s32>(size.getX() / 2, size.getY()),
                                  "A nice text\non the bottom\ncenter of the\nscreen",
                                  Text::Align::BOTTOM_CENTER);
        t.draw(renderBuffer);

        pos += offsetX;
    }

    {
        const Text t = createText(pos + Vec2<s32>(offsetX.getX() - 2, size.getY()),
                                  "The last text\nin the bottom\nright\ncorner",
                                  Text::Align::BOTTOM_RIGHT);
        t.draw(renderBuffer);
    }
}
