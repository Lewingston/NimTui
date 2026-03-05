#pragma once

#include "Widgets/Widget.h"
#include "Widgets/Grid.h"
#include "Style.h"
#include "Primitives/Bitmap.h"

namespace TUI::Demo {

    class ImageView : public Widget {

        public:

            ImageView(Vec2<s32> pos, Vec2<s32> size);

            virtual ~ImageView() = default;

            void setStyle(const Style& style);

            void draw(RenderBuffer& renderBuffer, Vec2<s32> offset) override;

            void loadFromFile(const std::string& filePath);

        private:

            void onResize() override;

            void updateImageSize();
            void updateImagePos(Vec2<s32> offset);

            [[nodiscard]] Bitmap::LoadImageResult loadImageToBitmap(const std::string& filePath) const;

            [[nodiscard]] std::optional<Bitmap> scaleImage(const Bitmap& image, Vec2<f32> scale) const;
            [[nodiscard]] std::optional<Bitmap> scaleImageToSize(const Bitmap& image, Vec2<u32> size) const;
            [[nodiscard]] Bitmap::LoadImageResult scaleImageToBitmap(const Bitmap& image, Vec2<f32> scale) const;

            Grid grid = Grid({0, 0}, getSize());

            Bitmap originalImage = Bitmap({0, 0});
            Bitmap scaledImage   = Bitmap({0, 0});

            std::string message;

    };
}
