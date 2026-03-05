
#include "ImageView.h"
#include "Primitives/Text.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb/stb_image_resize2.h"

using namespace TUI;
using namespace Demo;


ImageView::ImageView(Vec2<s32> pos, Vec2<s32> size) :
    Widget(pos, size)
{
    grid.enableOffset(false);
}


void ImageView::setStyle(const Style& style) {

    grid.setColors(style.primaryBackColor, style.secondaryBackColor);
}


void ImageView::onResize() {

    grid.setSize(getSize());

    updateImageSize();
}


void ImageView::updateImageSize() {

    auto result = scaleImageToSize(originalImage, getSize());
    if (result)
        scaledImage = std::move(*result);
}


void ImageView::updateImagePos(Vec2<s32> offset) {

    const Vec2<s32> imageOffset = {
        static_cast<s32>(getSize().getWidth() - scaledImage.getSize().getWidth()) / 2,
        static_cast<s32>(getSize().getHeight() - scaledImage.getSize().getHeight() / 2) / 2
    };

    scaledImage.setPos(getPos() + imageOffset + offset);
}


void ImageView::draw(RenderBuffer& buffer, Vec2<s32> offset) {

    grid.draw(buffer, offset + getPos());

    updateImagePos(offset);
    scaledImage.draw(buffer);

    const Text text(message, grid.getPos() + offset + getPos() + static_cast<Vec2<s32>>(grid.getSize()) / 2);
    text.draw(buffer);
}


void ImageView::loadFromFile(const std::string& filePath) {

    const bool success = originalImage.directLoad([&] -> Bitmap::LoadImageResult {

        return this->loadImageToBitmap(filePath);
    });

    if (!success) {
        message = std::string("Failed to load image: ") + filePath;
        return;
    }

    const Vec2<u32> size = {
        getSize().getWidth(),
        getSize().getHeight() * 2
    };

    auto result = scaleImageToSize(originalImage, size);
    if (!result.has_value()) {
        message  = std::string("Failed to scale image: ") + filePath;
        return;
    }

    message = "";

    scaledImage = std::move(result.value());
}


Bitmap::LoadImageResult ImageView::loadImageToBitmap(const std::string& filePath) const {

    s32 width    = 0;
    s32 height   = 0;
    s32 channels = 0;

    Bitmap::LoadImageResult result;

    result.pixelDataBuffer = std::unique_ptr<u8>(
        stbi_load(
            filePath.c_str(),
            &width,
            &height,
            &channels,
            0
        )
    );

    if (result.pixelDataBuffer) {
        result.size = Vec2<u32>(static_cast<u32>(width), static_cast<u32>(height));
        result.colorChannels = static_cast<u8>(channels);
    }

    return result;
}


std::optional<Bitmap> ImageView::scaleImageToSize(const Bitmap& image, Vec2<u32> size) const {

    f32 scaleX = static_cast<f32>(size.getX()) / static_cast<f32>(image.getSize().getWidth());
    f32 scaleY = static_cast<f32>(size.getY()) / static_cast<f32>(image.getSize().getHeight());

    if (scaleX > 1.0f) scaleX = 1.0f;
    if (scaleY > 1.0f) scaleY = 1.0f;

    return scaleImage(
        image,
        Vec2<f32>(
            std::min(scaleX, scaleY),
            std::min(scaleX, scaleY)
        )
    );
}


std::optional<Bitmap> ImageView::scaleImage(const Bitmap& image, Vec2<f32> scale) const {

    Bitmap result(image.getPos());

    const bool success = result.directLoad([&] -> Bitmap::LoadImageResult {

        return scaleImageToBitmap(image, scale);
    });

    if (!success)
        return {};

    return result;
}


Bitmap::LoadImageResult ImageView::scaleImageToBitmap(const Bitmap& image, Vec2<f32> scale) const {

    const Vec2<s32> scaledSize = {
        static_cast<s32>(static_cast<f32>(image.getSize().getWidth()) * scale.getX()),
        static_cast<s32>(static_cast<f32>(image.getSize().getHeight()) * scale.getY())
    };

    Bitmap::LoadImageResult result;

    result.pixelDataBuffer = std::unique_ptr<u8>(
        stbir_resize_uint8_srgb(
            image.getPixelDataBuffer().get(),
            static_cast<s32>(image.getSize().getWidth()),
            static_cast<s32>(image.getSize().getHeight()),
            0,
            nullptr,
            scaledSize.getWidth(),
            scaledSize.getHeight(),
            0,
            image.getColorChannels() == 4 ? STBIR_RGBA : STBIR_RGB
        )
    );

    if (result.pixelDataBuffer) {
        result.size = static_cast<Vec2<u32>>(scaledSize);
        result.colorChannels = image.getColorChannels();
    }

    return result;
}
