#pragma once

#include "Widgets/Widget.h"

#include <vector>
#include <string>

namespace TUI {

    class FileTree : public Widget {

        public:

            FileTree(Vec2<s32> pos, Vec2<u32> size);

            void draw(RenderBuffer& buffer, Vec2<s32> offset) override;

            void moveCursor(s32 move);
            std::string enter();
            std::string leave();

        private:

            [[nodiscard]] std::vector<std::string> getRootDirectories() const;
            [[nodiscard]] std::vector<std::string> getDirectoryEntries(const std::string& path) const;
            [[nodiscard]] std::string getCurrentPath() const;
            [[nodiscard]] std::string getCurrentSelectedPath() const;

            void drawTree(RenderBuffer& buffer, Vec2<s32> offset);
            void drawCurrentDir(RenderBuffer& buffer, Vec2<s32> offset);
            void drawCursor(RenderBuffer& buffer, Vec2<s32> offset);

            Color textColor = Color::WHITE;
            Color markColor = Color(25, 25, 25);

            std::vector<std::string> currentBranch;
            std::vector<std::string> currentDir;

            u32 currentPos = 0;
    };
}
