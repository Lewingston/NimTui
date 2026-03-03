
#include "ImageBrowser.h"
#include "Primitives/Line.h"
#include "Primitives/Text.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb/stb_image_resize2.h"

#include <algorithm>

using namespace TUI;


ImageBrowser::ImageBrowser(Vec2<s32> pos, Vec2<u32> size) :
    DemoPage(pos, size) 
{
    grid.enableOffset(true);
}


void ImageBrowser::setStyle(const Style& style) {

    DemoPage::setStyle(style);

    fileBrowser.setStyle(style);
    grid.setColors(style.primaryBackColor, style.secondaryBackColor);
}


void ImageBrowser::draw(RenderBuffer& renderBuffer, Vec2<s32> offset) {

    DemoPage::draw(renderBuffer, offset);

    fileBrowser.draw(renderBuffer, offset + getPos());

    Line line(Vec2<s32>(static_cast<s32>(fileBrowser.getSize().getWidth()), 0),
              getSize().getHeight(),
              "┃",
              Line::Mode::VERTICAL);
    line.setBackColor(getStyle().primaryBackColor);
    line.setFrontColor(getStyle().borderColor);

    line.draw(renderBuffer);

    grid.draw(renderBuffer, offset + getPos());

    scaledImage.draw(renderBuffer);

    const Text text(message, grid.getPos() + offset + getPos() + static_cast<Vec2<s32>>(grid.getSize() / 2));
    text.draw(renderBuffer);
}


bool ImageBrowser::handleKeyEvent(Console::KeyEvent keyEvent) {

    if (DemoPage::handleKeyEvent(keyEvent))
        return true;

    if (!keyEvent.pressed)
        return false;

    switch (keyEvent.keyCode) {

        case KeyCode::J:
        case KeyCode::DOWN: {
            fileBrowser.moveCursor(1);
            return true;
        }
        case KeyCode::K:
        case KeyCode::UP: {
            fileBrowser.moveCursor(-1);
            return true;
        }
        case KeyCode::U: {
            if (true /*hasFlag(keyEvent.keyModifiers, KeyModifier::CTRL_LEFT)*/) {
                fileBrowser.moveCursor(-10);
                return true;
            } else {
                return false;
            }
        }
        case KeyCode::D: {
            if (true /*hasFlag(keyEvent.keyModifiers, KeyModifier::CTRL_LEFT)*/) {
                fileBrowser.moveCursor(10);
                return true;
            } else {
                return false;
            }
        }
        case KeyCode::ENTER:
        case KeyCode::O: {
            fileSelected(fileBrowser.enter());
            return true;
        }
        case KeyCode::MINUS : {
            fileBrowser.leave();
            return true;
        }
        case KeyCode::LEFT:
        case KeyCode::H: {
            return true;
        }
        case KeyCode::RIGHT:
        case KeyCode::L: {
            return true;
        }
        default: {
            return false;
        }
    }

    return false;
}


void ImageBrowser::onResize() {

    const u32 width = std::min(45u, static_cast<u32>(getSize().getWidth() * 0.25));
    fileBrowser.setSize({width, getSize().getHeight()});

    grid.setPos({static_cast<s32>(width) + 1, 0});
    grid.setSize({getSize().getWidth() - width - 1, getSize().getHeight()});

    updateImagePosAndSize();
}


void ImageBrowser::updateImagePosAndSize() {

    auto result = scaleImageToSize(originalImage, grid.getSize());
    if (result)
        scaledImage = std::move(*result);

    updateImagePos();
}


void ImageBrowser::updateImagePos() {

    const Vec2<s32> imageOffset = {
        static_cast<s32>(grid.getSize().getWidth() - scaledImage.getSize().getWidth()) / 2,
        static_cast<s32>(grid.getSize().getHeight() - scaledImage.getSize().getHeight() / 2) / 2
    };

    scaledImage.setPos(grid.getPos() + imageOffset);
    originalImage.setPos(scaledImage.getPos());
}


void ImageBrowser::fileSelected(const FileBrowser::FileTreeEntry& file) {

    if (file.entryType != FileBrowser::DirEntryType::FILE)
        return;

    static constexpr std::array supportedFiles = {
        ".png", ".jpg", ".jpeg", ".PNG", ".JPG", ".JPEG"
    };

    if (std::find(supportedFiles.begin(), supportedFiles.end(), file.path.extension()) == supportedFiles.end()) {
        return;
    }

    loadImage(file.path.string());
}


void ImageBrowser::loadImage(const std::string& filePath) {

    const bool success = originalImage.directLoad([&] -> Bitmap::LoadImageResult {

        return this->loadImageToBitmap(filePath);
    });

    if (!success) {
        message = std::string("Failed to load image: ") + filePath;
        return;
    }

    const Vec2<u32> size = {
        grid.getSize().getWidth(),
        grid.getSize().getHeight() * 2
    };

    auto result = scaleImageToSize(originalImage, size);
    if (!result.has_value()) {
        message  = std::string("Failed to scale image: ") + filePath;
        return;
    }

    //message = "";

    scaledImage = std::move(result.value());

    updateImagePos();
}


Bitmap::LoadImageResult ImageBrowser::loadImageToBitmap(const std::string& filePath) const {

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


std::optional<Bitmap> ImageBrowser::scaleImageToSize(const Bitmap& image, Vec2<u32> size) const {

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


std::optional<Bitmap> ImageBrowser::scaleImage(const Bitmap& image, Vec2<f32> scale) const {

    Bitmap result(image.getPos());

    const bool success = result.directLoad([&] -> Bitmap::LoadImageResult {

        return scaleImageToBitmap(image, scale);
    });

    if (!success)
        return {};

    return result;
}


Bitmap::LoadImageResult ImageBrowser::scaleImageToBitmap(const Bitmap& image, Vec2<f32> scale) const {

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
