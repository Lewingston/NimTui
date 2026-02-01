
#include "ListView.h"
#include "Primitives/Text.h"

#include <algorithm>

using namespace TUI;


ListView::ListView(Vec2<s32> pos, Vec2<u32> size) :
    Widget(pos, size) {

}


void ListView::draw(RenderBuffer& buffer, Vec2<s32> offset) {

    Widget::draw(buffer, offset);

    drawListElements(buffer, getPos() + offset);
}


void ListView::drawListElements(RenderBuffer& buffer,
                                Vec2<s32> offset) {

    const u32 startIndex = scrollPosition;
    const u32 endIndex = std::min(startIndex + getSize().getHeight(), static_cast<u32>(elements.size()));

    for (u32 index = startIndex; index < endIndex; index++) {

        const bool selected = index == selectedElementIndex;
        const std::string& entry = elements.at(index);

        const s32 yOffset = static_cast<s32>(index) - static_cast<s32>(scrollPosition);

        drawListElement(entry, selected, buffer, offset + Vec2<s32>(0, yOffset));
    }
}


void ListView::drawListElement(const std::string& entry,
                               bool selected,
                               RenderBuffer& buffer,
                               Vec2<s32> offset)
{

    Text text(entry.substr(0, getSize().getWidth()), offset);

    if (selected) {

        text.setFrontColor(frontColorSelected);
        text.setBackColor(backColorSelected);

    } else {

        text.setBackColor(getBackColor());
        text.setFrontColor(frontColor);
    }

    text.draw(buffer);
}


void ListView::moveCursor(s32 steps) {

    if (getElementCount() <= 0)
        return;

    setCursorPosition(modifyCursorPosition(steps));
    scrollList(steps);
}


void ListView::enableWrapAround(bool enable) {

    wrapAround = enable;
}


void ListView::scrollList(s32 steps) {

    if (steps > 0)
        scrollDown(wrapAround);
    else if (steps < 0)
        scrollUp(wrapAround);
}


void ListView::scrollDown(bool wrapAround) {

    const s32 relativePosition = getRelativePosition();
    const s32 height = static_cast<s32>(getSize().getHeight()) - 1;

    if (relativePosition >= height) {

        scrollPosition = static_cast<u32>(static_cast<s32>(selectedElementIndex) - height);

    } else if (wrapAround) {

        scrollUp(false);
    }
}


void ListView::scrollUp(bool wrapAround) {

    if (getRelativePosition() < 0) {

        scrollPosition = selectedElementIndex;

    } else if (wrapAround) {

        scrollDown(false);
    }
}


s32 ListView::getRelativePosition() const {

    return static_cast<s32>(selectedElementIndex) -
           static_cast<s32>(scrollPosition);
}


u32 ListView::modifyCursorPosition(s32 steps) const {

    s32 newPosition = static_cast<s32>(selectedElementIndex) + steps;

    if (wrapAround) {

        newPosition = newPosition % static_cast<s32>(getElementCount());

        if (newPosition < 0)
            newPosition = static_cast<s32>(getElementCount()) + newPosition;
    }

    newPosition = std::clamp(newPosition, 0, static_cast<s32>(elements.size() - 1));

    return static_cast<u32>(newPosition);
}


void ListView::moveCursorToFirstElement() {

    setCursorPosition(0);
}


void ListView::moveCursorToLastElement() {

    setCursorPosition(static_cast<u32>(getElementCount()) - 1);
}


void ListView::setCursorPosition(u32 position) {

    if (getElementCount() == 0)
        return;

    selectedElementIndex = position % static_cast<u32>(getElementCount());
}


void ListView::addElement(const std::string& entry) {

    elements.push_back(entry);
}


void ListView::addElements(const std::vector<std::string>& entries) {

    elements.insert(elements.end(), entries.begin(), entries.end());
}


void ListView::removeElement(const std::string& entry) {

    elements.erase(std::remove(elements.begin(), elements.end(), entry), elements.end());

    selectedElementIndex = std::min(static_cast<u32>(elements.size() - 1), selectedElementIndex);
}


void ListView::removeAllElements() {

    elements.clear();

    selectedElementIndex = 0;
}


const std::string& ListView::getSelectedElement() const {

    static const std::string none;

    if (elements.empty())
        return none;

    return elements.at(selectedElementIndex);
}


std::size_t ListView::getElementCount() const {

    return elements.size();
}


u32 ListView::getCursorPosition() const {

    return selectedElementIndex;
}


const std::vector<std::string> ListView::getAllElements() const noexcept {

    return elements;
}


const std::string& ListView::getElementAt(u32 pos) const {

    return elements.at(pos);
}
