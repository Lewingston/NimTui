
#include "RectDemo.h"
#include "Primitives/Rect.h"

using namespace TUI;
using namespace Demo;


RectDemo::RectDemo(Vec2<s32> pos, Vec2<u32> size) :
    DemoPage(pos, size)
{
    setupGrid();
}


void RectDemo::setStyle(const Style& style) {

    grid.setColors(style.primaryBackColor, style.secondaryBackColor);
    grid.setTextColor(style.borderColor);
}


void RectDemo::setupGrid() {

    grid.setGridSize({24, 12});
    grid.enableNumbers(true);
    grid.enableOffset(false);
}


void RectDemo::draw(RenderBuffer& renderBuffer, Vec2<s32> offset) {

    grid.draw(renderBuffer, getPos() + offset);

    Rect rect1({2, 1}, {20, 10});
    rect1.setBorder({Rect::Border::Style::VERY_THICK, Color::GRAY});
    rect1.setBackColor(Color(40, 40, 40));
    rect1.setBorderInset(Rect::BorderInset::HORIZONTAL);
    rect1.draw(renderBuffer);

    Rect rect2({26, 1}, {20, 10});
    rect2.setBorder({Rect::Border::Style::THICK, Color::GRAY});
    rect2.setBackColor(Color(40, 40, 40));
    rect2.setBorderInset(Rect::BorderInset::HORIZONTAL);
    rect2.draw(renderBuffer);

    Rect rect3({50, 1}, {20, 10});
    rect3.setBorder({Rect::Border::Style::MEDIUM, Color::GRAY});
    rect3.setBackColor(Color(40, 40, 40));
    rect3.setBorderInset(Rect::BorderInset::HORIZONTAL);
    rect3.draw(renderBuffer);

    Rect rect4({74, 1}, {20, 10});
    rect4.setBorder({Rect::Border::Style::THIN, Color::GRAY});
    rect4.setBackColor(Color(40, 40, 40));
    rect4.setBorderInset(Rect::BorderInset::HORIZONTAL);
    rect4.draw(renderBuffer);

    Rect rect5({98, 1}, {20, 10});
    rect5.setBorder({Rect::Border::Style::NONE, Color::GRAY});
    rect5.setBackColor(Color(40, 40, 40));
    rect5.setBorderInset(Rect::BorderInset::HORIZONTAL);
    rect5.draw(renderBuffer);

    Rect rect6({2, 13}, {20, 10});
    rect6.setBorder({Rect::Border::Style::VERY_THICK, Color::GRAY});
    rect6.setBackColor(Color(40, 40, 40));
    rect6.setBorderInset(Rect::BorderInset::VERTICAL);
    rect6.draw(renderBuffer);

    Rect rect7({26, 13}, {20, 10});
    rect7.setBorder({Rect::Border::Style::THICK, Color::GRAY});
    rect7.setBackColor(Color(40, 40, 40));
    rect7.setBorderInset(Rect::BorderInset::VERTICAL);
    rect7.draw(renderBuffer);

    Rect rect8({50, 13}, {20, 10});
    rect8.setBorder({Rect::Border::Style::MEDIUM, Color::GRAY});
    rect8.setBackColor(Color(40, 40, 40));
    rect8.setBorderInset(Rect::BorderInset::VERTICAL);
    rect8.draw(renderBuffer);

    Rect rect9({74, 13}, {20, 10});
    rect9.setBorder({Rect::Border::Style::THIN, Color::GRAY});
    rect9.setBackColor(Color(40, 40, 40));
    rect9.setBorderInset(Rect::BorderInset::VERTICAL);
    rect9.draw(renderBuffer);

    Rect rect10({98, 13}, {20, 10});
    rect10.setBorder({Rect::Border::Style::NONE, Color::GRAY});
    rect10.setBackColor(Color(40, 40, 40));
    rect10.setBorderInset(Rect::BorderInset::VERTICAL);
    rect10.draw(renderBuffer);
}


void RectDemo::onResize() {

    grid.setSize(getSize());
}
