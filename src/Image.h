#pragma once

#include "Types.h"
#include "Vec.h"

#include <string>
#include <memory>

namespace TUI {

    class RenderBuffer;

    class Image {

        public:

            Image() = default;

            virtual ~Image() = default;

            [[nodiscard]] static Image loadFromFile(const std::string& file);

            void setPos(Vec2<s32> pos) { this->pos = pos; }

            void blit(RenderBuffer& renderBuffer, Vec2<s32> offset) const;

            [[nodiscard]] Image scale(f32 scaleX, f32 scaleY) const;
            [[nodiscard]] Image scaleToSize(Vec2<u32> size) const;

            [[nodiscard]] Vec2<u32> getSize() const noexcept;

            [[nodiscard]] bool isValid() const noexcept { return data != nullptr; }

        private:

            void copyParameters(const Image& image);

            s32 width         = 0;
            s32 height        = 0;
            s32 colorChannels = 0;
            s32 bitDepth      = 0;

            // Multiple images can share the same image data
            std::shared_ptr<unsigned char> data;

            Vec2<s32> pos { 0, 0 };
    };
}
