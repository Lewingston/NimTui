
#include "Text.h"
#include "Console/RenderBuffer.h"

using namespace TUI;


Text::Text(const std::string& text, Vec2<s32> pos) :
    Drawable(pos),
    text(text) {

}


void Text::draw(RenderBuffer& buffer) const {

    for (u32 ii = 0; ii < text.size(); ii++) {

        const s32 posX = getPos().getX() + static_cast<s32>(ii);
        const s32 posY = getPos().getY();

        if (posX < 0 || posY < 0)
            continue;

        buffer.set({static_cast<u32>(posX), static_cast<u32>(posY)},
                   {
                   text.substr(ii, 1),
                    frontColor,
                    backColor
                   });
    }
}
