#pragma once

#include "../DemoPage.h"
#include "Widgets/FileBrowser.h"
#include "Widgets/Grid.h"
#include "Primitives/Bitmap.h"

namespace TUI {

    class ImageBrowser : public DemoPage {

        public:

            ImageBrowser(Vec2<s32> pos, Vec2<u32> size);

            virtual ~ImageBrowser() = default;

            void setStyle(const Style& style) override;

            void draw(RenderBuffer& renderBuffer, Vec2<s32> offset) override;

            bool handleKeyEvent(Console::KeyEvent keyEvent) override;

        private:

            void onResize() override;
            void updateImagePosAndSize();
            void updateImagePos();

            void fileSelected(const FileBrowser::FileTreeEntry& file);

            void loadImage(const std::string& filePath);
            [[nodiscard]] Bitmap::LoadImageResult loadImageToBitmap(const std::string& filePath) const;

            [[nodiscard]] std::optional<Bitmap> scaleImage(const Bitmap& image, Vec2<f32> scale) const;
            [[nodiscard]] std::optional<Bitmap> scaleImageToSize(const Bitmap& image, Vec2<u32> size) const;
            [[nodiscard]] Bitmap::LoadImageResult scaleImageToBitmap(const Bitmap& image, Vec2<f32> scale) const;

            FileBrowser fileBrowser = FileBrowser({0, 0}, {0, 0});

            Grid grid = Grid({0, 0}, {0, 0});

            Bitmap originalImage = Bitmap({0, 0});
            Bitmap scaledImage   = Bitmap({0, 0});

            std::string message;

    };
}
