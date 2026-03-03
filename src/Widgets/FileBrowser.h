#pragma once

#include "ListView.h"

#include <filesystem>

namespace TUI {

    class FileBrowser : public ListView {

        public:

            enum class DirEntryType : u8 {

                FILE,
                DIR,
                LINK,
                DRIVE
            };

            struct FileTreeEntry {

                std::filesystem::path path;
                u32                   level = 0;
                DirEntryType          entryType;
                char                  driveLetter = 0;
            };
            FileBrowser(Vec2<s32> pos, Vec2<u32> size);

            virtual ~FileBrowser() = default;

            FileTreeEntry enter();
            FileTreeEntry leave();

        private:

            void update(const std::filesystem::path& path);

            std::vector<FileTreeEntry> buildParentDirEntries(const std::filesystem::path& path) const;

            [[nodiscard]] std::string buildEntryName(const FileTreeEntry& entry) const;

            void updateListViewElements();

            [[nodiscard]] std::vector<FileTreeEntry> getRootDirectories() const;
            [[nodiscard]] std::vector<FileTreeEntry> getDirectoryEntries(const std::filesystem::path& path) const;
            [[nodiscard]] FileTreeEntry getFileTreeEntry(const std::filesystem::directory_entry& entry) const;
            [[nodiscard]] u32 getDirectoryDepth(const std::filesystem::path& path) const;

            [[nodiscard]] std::filesystem::path getCurrentPath() const;
            [[nodiscard]] const FileTreeEntry& getCurrentSelectedElement() const;

            std::vector<FileTreeEntry> fileEntries;

            u32 currentDirDepth = 0;

            char currentDrive = 0;
    };
}
