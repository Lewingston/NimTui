#pragma once

#include "Types.h"
#include "Color.h"
#include "Vec.h"

#include <vector>
#include <memory>

#include <windows.h>

namespace TUI {

    /*
    class ConsoleBuffer {

        public:

            ConsoleBuffer();
            ConsoleBuffer(HANDLE bufferHandle);
            virtual ~ConsoleBuffer();

            void setActive();
            void write(const std::string& str);
            void setCursorPos(u32 x, u32 y);

        private:

            HANDLE bufferHandle;

            bool newBuffer = false;
    };
    */


    /*
    class RenderBuffer {

        public:

            struct CharInfo
            {
                std::string character = " ";
                Color backColor  = Color::BLACK;
                Color frontColor = Color::WHITE;

                [[nodiscard]] std::string getTermSeq() const;
                [[nodiscard]] std::string colorToString(Color color) const;
            };

            RenderBuffer(u32 width, u32 height);
            RenderBuffer(Vec2<u32> size);

            RenderBuffer(const RenderBuffer&) = delete;
            RenderBuffer& operator=(const RenderBuffer&) = delete;

            virtual ~RenderBuffer() = default;

            [[nodiscard]] Vec2<u32> getSize() const noexcept { return size; }

            void set(Vec2<u32> pos, std::string character, Color backColor, Color frontColor);
            [[nodiscard]] const CharInfo& get(Vec2<u32> pos) const;

            void print(Vec2<s32> pos, std::string& text, Color color);

            void blit(ConsoleBuffer& console);

        private:

            Vec2<u32> size;

            std::vector<CharInfo> characters;
    };
    */


    /*
    class ConsoleWindow {

        public:

            ConsoleWindow();
            virtual ~ConsoleWindow() = default;

            [[nodiscard]] RenderBuffer& getRenderBuffer();

            void show();
            void hide();

            void flip();

        private:

            std::unique_ptr<ConsoleBuffer> stdBuffer;

            std::unique_ptr<RenderBuffer> renderBuffer;

    };
    */
}
