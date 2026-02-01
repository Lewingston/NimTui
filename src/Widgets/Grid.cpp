
#include "Grid.h"
#include "Console/RenderBuffer.h"
#include "Primitives/Text.h"

using namespace TUI;


Grid::Grid(Vec2<s32> pos, Vec2<u32> size) :
    Widget(pos, size) { }


void Grid::draw(RenderBuffer& buffer, Vec2<s32> offset) {

    drawGrid(buffer, offset);

    if (showNumbers)
        drawNumbers(buffer, offset);
}


void Grid::drawGrid(RenderBuffer& buffer, Vec2<s32> offset) {

    const Vec2<s32> gridSize { static_cast<s32>(this->gridSize.getX()), static_cast<s32>(this->gridSize.getY())};
    const Vec2<s32> gridOffset = gridSize - getGridOffset();

    for (s32 y = 0; y < static_cast<s32>(getSize().getHeight()); y++) {
        for (s32 x = 0; x < static_cast<s32>(getSize().getWidth()); x++) {

            const s32 posX = x + offset.getX();
            const s32 posY = y + offset.getY();

            const Vec2<u32> pos = { static_cast<u32>(posX), static_cast<u32>(posY) };

            const s32 gridX = ((x + gridOffset.getX()) / gridSize.getWidth()) % 2;
            const s32 gridY = ((y + gridOffset.getY()) / gridSize.getHeight()) % 2;

            Color color { 0, 0, 0 };
            if (gridY == 0) {

                if (gridX == 0)
                    color = color1;
                else if (gridX == 1)
                    color = color2;

            } else if (gridY == 1) {

                if (gridX == 0)
                    color = color2;
                else if (gridX == 1)
                    color = color1;
            }

            buffer.set(pos, { " ", buffer.get(pos).frontColor, color });
        }
    }
}


void Grid::drawNumbers(RenderBuffer& buffer, Vec2<s32> offset) {

    const Vec2<s32> gridOffset = getGridOffset();

    const u32 countX = getSize().getWidth() / gridSize.getWidth();
    const u32 countY = getSize().getHeight() / gridSize.getHeight();

    for (s32 y = 0; y < static_cast<s32>(countY); y++) {
        for (s32 x = 0; x < static_cast<s32>(countX); x++) {

            const s32 posX = gridOffset.getX() + (x * static_cast<s32>(gridSize.getWidth())) + offset.getX();
            const s32 posY = gridOffset.getY() + (y * static_cast<s32>(gridSize.getHeight())) + offset.getY();

            //const std::string str = std::to_string(x) + std::to_string(y);
            const std::string str = getGridText(x, y);
            Text text = Text(str, {posX, posY});
            text.setFrontColor(textColor);
            text.setBackColor(buffer.get({static_cast<u32>(posX), static_cast<u32>(posY)}).backColor);

            text.draw(buffer);
        }
    }
}


void Grid::setColors(Color color1, Color color2) {

    this->color1 = color1;
    this->color2 = color2;
}


void Grid::setTextColor(Color color) {

    textColor = color;
}


void Grid::setGridSize(Vec2<u32> size) {

    gridSize = size;
}


void Grid::enableNumbers(bool enable) {

    showNumbers = enable;
}


Vec2<s32> Grid::getGridOffset() const {

    const s32 gridWidth = static_cast<s32>(gridSize.getWidth());
    const s32 gridHeight = static_cast<s32>(gridSize.getHeight());

    const s32 width = static_cast<s32>(getSize().getWidth());
    const s32 height = static_cast<s32>(getSize().getHeight());

    //const s32 gridOffsetX = gridWidth - (width % gridWidth) / 2;
    //const s32 gridOffsetY = gridHeight - (height % gridHeight) / 2;

    const s32 gridOffsetX = width % gridWidth / 2;
    const s32 gridOffsetY = height % gridHeight / 2;

    return { gridOffsetX, gridOffsetY };
}


std::string Grid::getGridText(s32 x, s32 y) const {

    std::string str;

    if (x <= 9)
        str += "0";

    str += std::to_string(x);

    if (y <= 9)
        str += "0";

    str += std::to_string(y);

    return str;
}
