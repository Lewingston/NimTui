#pragma once

#include "Widgets/Widget.h"
#include "Image.h"

#include <string>

namespace TUI {

    class ImageView : public Widget {

        public:

            ImageView(Vec2<s32> pos, Vec2<u32> size);

            void draw(RenderBuffer& buffer, Vec2<s32> offset) override;

            void loadImage(const std::string& path);

            void setImage(Image& image) { this->image = image; }

            [[nodiscard]] const Image& getImage() const noexcept { return image; }

        private:

            Image image;
    };
}
