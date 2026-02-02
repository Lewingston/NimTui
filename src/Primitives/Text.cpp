
#include "Text.h"
#include "Console/RenderBuffer.h"

using namespace TUI;


Text::Text(const std::string& text, Vec2<s32> pos) :
    Drawable(pos),
    text(text) {

}


void Text::draw(RenderBuffer& buffer) const {

    s32 posX = getPos().getX();
    const s32 posY = getPos().getY();

    for (u32 ii = 0; ii < text.size();) {

        const u8 byteCount = Utf8Char::getByteCount(static_cast<u8>(text.at(ii)));

        if (posX < 0 || posY < 0)
            continue;

        buffer.set({static_cast<u32>(posX), static_cast<u32>(posY)},
                   {
                   Utf8Char(text.c_str() + ii),
                    frontColor,
                    backColor
                   });

        ii += byteCount;
        posX += 1;
    }
}
