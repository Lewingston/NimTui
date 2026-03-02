#pragma once

#include "Widgets/Widget.h"

#include <functional>

namespace TUI {

    class DemoPage : public Widget {

        public:

            DemoPage(Vec2<s32> pos, Vec2<u32> size);

            virtual ~DemoPage() = default;

            virtual bool handleKeyEvent(Console::KeyEvent keyEvent) override;

            virtual void onLeave(std::function<void()> callback);

        protected:

            virtual void leaveMenu();

        private:

            std::function<void()> onLeaveCallback;

    };
}
