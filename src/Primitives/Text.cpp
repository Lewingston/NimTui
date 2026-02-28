
#include "Text.h"
#include "Console/RenderBuffer.h"
#include "Common/Unicode.h"

using namespace TUI;


Text::Text(const std::string& text, Vec2<s32> pos) :
    Drawable(pos),
    text(text) {

}


void Text::draw(RenderBuffer& buffer) const {

    s32 posX = getPos().getX();
    const s32 posY = getPos().getY();

    for (u32 ii = 0; ii < text.size();) {

        //if (posX < 0 || posY < 0)
        //    continue;

        const auto info = Unicode::getInfo(text, ii);

        buffer.set({ static_cast<u32>(posX), static_cast<u32>(posY) },
                   { text.substr(ii, info.byteCount), frontColor, backColor });

        ii += info.byteCount;

        posX += info.width;
    }
}
