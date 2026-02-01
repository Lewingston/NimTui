#pragma once

#include "Console.h"

#include <memory>
#include <functional>

namespace TUI {

    class RenderBuffer;

    class ConsoleWindow {

        public:

            ConsoleWindow();

            virtual ~ConsoleWindow() = default;

            [[nodiscard]] std::weak_ptr<RenderBuffer> getRenderBuffer();

            [[nodiscard]] const Vec2<u32>& getSize() const;

            [[nodiscard]] Console& getConsole() noexcept { return console; }

            void show();
            void hide();

            void onResize(std::function<void()> onResizeCallback);
            void onKeyInput(std::function<void(Console::KeyEvent)> onKeyInputCallback);

            void readConsoleInput();

        private:

            void handleConsoleInputEvent(const Console::InputEvent& inputEvent);
            void handleKeyEvent(const Console::KeyEvent& keyEvent);
            void handleResizeEvent(const Console::ResizeEvent& reiszeEvent);

            Console console;

            std::shared_ptr<RenderBuffer> renderBuffer;

            std::function<void()> onResizeCallback;
            std::function<void(Console::KeyEvent)> onKeyInputCallback;

    };
}
