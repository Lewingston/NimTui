#pragma once

#include "ListView.h"

#include <limits>

namespace TUI {

    class FileBrowser : public ListView {

        public:

            FileBrowser(Vec2<s32> pos, Vec2<u32> size);

            virtual ~FileBrowser() = default;

            std::string enter();
            std::string leave();

        private:

            void update(const std::string& path);

            [[nodiscard]] std::vector<std::string> getRootDirectories() const;
            [[nodiscard]] std::vector<std::string> getDirectoryEntries(const std::string& path) const;
            [[nodiscard]] std::string getCurrentPath(u32 depthLimit = std::numeric_limits<u32>::max()) const;
            [[nodiscard]] std::string getCurrentSelectedPath() const;

            u32 currentDirDepth = 0;
    };
}
