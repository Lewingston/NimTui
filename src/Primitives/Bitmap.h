#pragma once

#include "Drawable.h"
#include "Color.h"

#include <functional>
#include <memory>

namespace TUI {

    class Bitmap : public Drawable {

        public:

            Bitmap(Vec2<s32> pos);

            // Disable copy
            Bitmap(const Bitmap&) = delete;
            Bitmap& operator=(const Bitmap&) = delete;

            // Enable move
            Bitmap(Bitmap&&) = default;
            Bitmap& operator=(Bitmap&&) = default;

            virtual ~Bitmap() = default;

            virtual void draw(RenderBuffer& buffer) const;

            [[nodiscard]] Color get(Vec2<u32> pos) const;

            [[nodiscard]] Vec2<u32> getSize() const noexcept { return size; }

            [[nodiscard]] u8 getColorChannels() const noexcept { return colorChannels; }

            [[nodiscard]] const std::unique_ptr<u8>& getPixelDataBuffer() const { return pixelDataBuffer; }

            struct LoadImageResult {

                std::unique_ptr<u8> pixelDataBuffer; // pointer to image data; must be initialized by load function
                                                     // return a null pointer in the result to indicate the load failed
                Vec2<u32>           size;            // image size
                u8                  colorChannels;   // number of color channels
            };

            bool directLoad(std::function<LoadImageResult()> callback);

        private:

            void reset();

            [[nodiscard]] std::size_t posToIndex(Vec2<u32> pos) const noexcept;

            Vec2<u32> size {0, 0};

            u8 colorChannels = 0;

            std::unique_ptr<u8> pixelDataBuffer;

    };
}
