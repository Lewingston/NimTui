#pragma once

#include "Widgets/Widget.h"
#include "Style.h"

#include <functional>

namespace TUI {

    class DemoPage : public Widget {

        public:

            DemoPage(Vec2<s32> pos, Vec2<u32> size);

            virtual ~DemoPage() = default;

            virtual void setStyle(const Style& style);

            virtual bool handleKeyEvent(Console::KeyEvent keyEvent) override;

            virtual void onLeave(std::function<void()> callback);

        protected:

            virtual void leaveMenu();

            [[nodiscard]] const Style& getStyle() const noexcept { return style; }

        private:

            std::function<void()> onLeaveCallback;

            Style style = DEFAULT_STYLE;

    };
}
