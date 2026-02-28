
#include "Image.h"
#include "Color.h"
//#include "ConsoleWindow.h"

/*
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
*/

/*
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb/stb_image_resize2.h"
*/

#include <stdexcept>
#include <iostream>

using namespace TUI;


void Image::copyParameters(const Image& image)
{
    data          = image.data;
    width         = image.width;
    height        = image.height;
    bitDepth      = image.bitDepth;
    colorChannels = image.colorChannels;
}


Image Image::loadFromFile(const std::string& file) {

    Image image;

    /*
    image.data = std::shared_ptr<unsigned char>(
        stbi_load(
            file.c_str(),
            &image.width,
            &image.height,
            &image.colorChannels,
            0
        )
    );
    */

    if (image.data == nullptr) {
        throw std::runtime_error("Failed to laod image: " + file);
    }

    std::cout << "Image loaded: width=" << image.width <<
        " height=" << image.height <<
        " channels=" << image.colorChannels <<
        " bitDepth=" << image.bitDepth << '\n';

    return image;
}


Vec2<u32> Image::getSize() const noexcept {

    return Vec2<u32>(
        static_cast<u32>(width),
        static_cast<u32>(height)
    );
}


void Image::blit(RenderBuffer& renderBuffer, Vec2<s32> offset) const {

    if (data == nullptr)
        return;

    /*
    for (s32 y = 0; y < height; y++) {

        const s32 posY = pos.getY() + (y / 2) + offset.getY();

        for (s32 x = 0; x < width; x++) {

            const s32 posX = pos.getX() + x + offset.getX();

            if (posX < 0 || posY < 0)
                continue;

            //if (posX >= static_cast<s32>(renderBuffer.getSize().getWidth()))
            //    break;

            const Vec2<u32> pos = {
                static_cast<u32>(posX),
                static_cast<u32>(posY)
            };

            const u32 index = static_cast<u32>((y * width + x) * colorChannels);
            const Color color(
                static_cast<u8>(data.get()[index]),
                static_cast<u8>(data.get()[index + 1]),
                static_cast<u8>(data.get()[index + 2])
            );

            static constexpr std::string pixChar = "▄";

            if (y % 2 == 0) {

                renderBuffer.set(pos, pixChar, color, Color::BLACK);

            } else {

                const auto& charInfo = renderBuffer.get(pos);
                renderBuffer.set(pos, pixChar, charInfo.backColor, color);

            }
        }

        if (posY >= static_cast<s32>(renderBuffer.getSize().getHeight()))
            break;

    }
    */
}


Image Image::scale(f32 scaleX, f32 scaleY) const {


    if (data == nullptr)
        return Image();

    Image scaledImage;
    scaledImage.bitDepth = bitDepth;
    scaledImage.colorChannels = colorChannels;
    scaledImage.width  = static_cast<s32>(scaleX * static_cast<f32>(width));
    scaledImage.height = static_cast<s32>(scaleY * static_cast<f32>(height));

    /*
    scaledImage.data = std::shared_ptr<unsigned char>(
        stbir_resize_uint8_srgb(
            data.get(), // input pixel data
            width,      // input width
            height,     // input height
            0,          // input stride
            nullptr,
            scaledImage.width,
            scaledImage.height,
            0,
            colorChannels == 4 ? STBIR_RGBA : STBIR_RGB
        )
    );
    */

    std::cout << "Image loaded: width=" << scaledImage.width <<
        " height=" << scaledImage.height <<
        " channels=" << scaledImage.colorChannels <<
        " bitDepth=" << scaledImage.bitDepth << '\n';

    return scaledImage;
}


Image Image::scaleToSize(Vec2<u32> size) const {

    float scaleX = static_cast<float>(size.getX()) / static_cast<float>(width);
    float scaleY = static_cast<float>(size.getY()) / static_cast<float>(height) * 2.0f;

    // The image is smaller than the requested size: do not scale
    if (scaleX >= 1.0f && scaleY >= 1.0f) {
        return *this;
    }

    return scale(
        std::min(scaleX, scaleY),
        std::min(scaleX, scaleY)
    );
}
