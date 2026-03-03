
#include "Bitmap.h"
#include "Console/RenderBuffer.h"

#include <limits>
#include <string>

using namespace TUI;

Bitmap::Bitmap(Vec2<s32> pos) :
    Drawable(pos) {}


void Bitmap::draw(RenderBuffer& buffer) const {

    if (!pixelDataBuffer)
        return;

    for (u32 y = 0; y < size.getHeight(); y += 2) {

        for (u32 x = 0; x < size.getWidth(); x++) {

            const Vec2<s32> pos = Vec2<s32>(static_cast<s32>(x), static_cast<s32>(y));

            const Color topPixel = get(pos);
            const Color bottomPixel = get(pos + Vec2<s32>(0, 1));

            static constexpr std::string c = "▄";

            buffer.set(getPos() + Vec2<s32>(pos.getX(), pos.getY() / 2), {c, bottomPixel, topPixel});
        }
    }
}


bool Bitmap::directLoad(std::function<LoadImageResult()> callback) {

    if (!callback)
        return false;

    LoadImageResult result = callback();

    if (!result.pixelDataBuffer)
        return false;

    pixelDataBuffer = std::move(result.pixelDataBuffer);
    size            = result.size;
    colorChannels   = result.colorChannels;

    return true;
}


void Bitmap::reset() {

    pixelDataBuffer.reset();
    size = {0, 0};
    colorChannels = 0;
}


Color Bitmap::get(Vec2<u32> pos) const {

    const std::size_t index = posToIndex(pos);
    if (index == std::numeric_limits<std::size_t>::max())
        return Color::BLACK;

    return Color {
        pixelDataBuffer.get()[index],
        pixelDataBuffer.get()[index + 1],
        pixelDataBuffer.get()[index + 2]
    };
}


std::size_t Bitmap::posToIndex(Vec2<u32> pos) const noexcept {

    if (pos.getX() >= size.getWidth() ||
        pos.getY() >= size.getHeight())
        return std::numeric_limits<std::size_t>::max();

    return (size.getWidth() * pos.getY() + pos.getX()) * colorChannels;
}
