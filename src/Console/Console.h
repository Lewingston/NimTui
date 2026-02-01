#pragma once

#include "Vec.h"
#include "Types.h"
#include "KeyCode.h"

#include <variant>
#include <optional>

#include <windows.h>

namespace TUI {

    class Console {

        public:

            struct KeyEvent {

                KeyEvent() = default;
                KeyEvent(const KEY_EVENT_RECORD& keyEventRecord);

                bool        pressed      = false;
                KeyCode     keyCode      = KeyCode::NONE;
                KeyModifier keyModifiers = KeyModifier::NONE;
                char        asciiChar    = 0;
            };

            struct ResizeEvent {

                ResizeEvent() = default;
                ResizeEvent(const WINDOW_BUFFER_SIZE_RECORD& bufferSizeRecord);

                Vec2<u32> size;
            };

            struct InputEvent {

                InputEvent(const INPUT_RECORD& inputRecord);

                std::variant<ResizeEvent, KeyEvent> event;
            };

            Console();

            virtual ~Console();

            void enterAlternateMode();
            void leaveAlternateMode();

            void enableConsoleWindowInputEvents();

            [[nodiscard]] Vec2<u32> readConsoleSize() const;

            [[nodiscard]] std::optional<InputEvent> readConsoleInput() const;

            void showCursor();
            void hideCursor();

        private:

            HANDLE outputHandle;
            HANDLE inputHandle;

    };
}
