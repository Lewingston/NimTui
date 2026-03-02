#pragma once

#include "Widget.h"
#include "Style.h"

#include <vector>
#include <string>

namespace TUI {

    class ListView : public Widget {

        public:

            ListView(Vec2<s32> pos, Vec2<u32> size);

            virtual ~ListView() = default;

            void draw(RenderBuffer& buffer, Vec2<s32> offset) override;

            void addElement(const std::string& entry);
            void addElements(const std::vector<std::string>& entries);
            void removeElement(const std::string& entry);
            void removeAllElements();

            void setStyle(const Style& style);

            [[nodiscard]] const std::string& getSelectedElement() const;

            [[nodiscard]] u32 getCursorPosition() const;

            [[nodiscard]] std::size_t getElementCount() const;

            [[nodiscard]] const std::vector<std::string> getAllElements() const noexcept;

            [[nodiscard]] const std::string& getElementAt(u32 pos) const;

            void enableWrapAround(bool enable);

            void moveCursor(s32 steps);
            void setCursorPosition(u32 position);
            void moveCursorToFirstElement();
            void moveCursorToLastElement();

        protected:

            virtual void drawListElements(RenderBuffer& buffer, Vec2<s32> offset);

            virtual void drawListElement(u32           index,
                                         RenderBuffer& buffer,
                                         Vec2<s32>     offset);

            virtual void drawListElement(const std::string& entry,
                                         bool               selected,
                                         RenderBuffer&      buffer,
                                         Vec2<s32>          offset);

            [[nodiscard]] u32 getScrollPosition() const noexcept { return scrollPosition; }

        private:

            [[nodiscard]] u32 modifyCursorPosition(s32 steps) const;
            void scrollList(s32 steps);
            void scrollUp(bool wrapAround);
            void scrollDown(bool wrapAround);

            [[nodiscard]] s32 getRelativePosition() const;

            std::vector<std::string> elements;

            u32 selectedElementIndex = 0;
            u32 scrollPosition = 0;

            bool wrapAround = true;

            Style style = DEFAULT_STYLE;
    };
}
