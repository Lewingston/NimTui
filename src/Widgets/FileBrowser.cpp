
#include "FileBrowser.h"

#include <filesystem>

#include <ranges>

#include <windows.h>

using namespace TUI;


FileBrowser::FileBrowser(Vec2<s32> pos, Vec2<u32> size) :
    ListView(pos, size),
    fileEntries(getRootDirectories())
{

    updateListViewElements();
}


FileBrowser::FileTreeEntry FileBrowser::enter() {

    const FileTreeEntry entry = getCurrentSelectedElement();

    if (std::filesystem::is_directory(entry.path)) {

        if (entry.entryType == DirEntryType::DRIVE)
            currentDrive = entry.driveLetter;

        update(entry.path);
    }

    return entry;
}


FileBrowser::FileTreeEntry FileBrowser::leave() {

    if (currentDirDepth == 0)
        return getCurrentSelectedElement();

    currentDirDepth -= 1;
    if (currentDirDepth == 0) {

        fileEntries = getRootDirectories();

        updateListViewElements();

        return getCurrentSelectedElement();

    } else {

        update(getCurrentPath());

        return getCurrentSelectedElement();
    }
}


void FileBrowser::update(const std::filesystem::path& path) {

    if (!std::filesystem::exists(path))
        return;

    if (!std::filesystem::is_directory(path)) {

    }

    fileEntries.clear();

    const auto parentDirEntries = buildParentDirEntries(path);
    fileEntries.insert(fileEntries.end(), parentDirEntries.rbegin(), parentDirEntries.rend());

    currentDirDepth = static_cast<u32>(fileEntries.size());

    const auto entries = getDirectoryEntries(path);
    fileEntries.insert(fileEntries.end(), entries.begin(), entries.end());

    updateListViewElements();
}


std::vector<FileBrowser::FileTreeEntry> FileBrowser::buildParentDirEntries(const std::filesystem::path& path) const {

    std::vector<FileTreeEntry> result;

    u32 depth = getDirectoryDepth(path);
    std::filesystem::path parentDirs = path;
    while (!parentDirs.empty()) {

        auto newDirs = parentDirs.parent_path();
        if (parentDirs == newDirs) {
            result.emplace_back(parentDirs, depth, DirEntryType::DRIVE, FileType::NOT_A_FILE, currentDrive);
            break;
        }

        result.emplace_back(parentDirs, depth, DirEntryType::DIR);

        parentDirs = newDirs;
        depth--;
    }

    return result;
}


std::string FileBrowser::buildEntryName(const FileTreeEntry& entry) const {

    if (entry.entryType == DirEntryType::DRIVE) {
        return std::string(1, entry.driveLetter) + ":/";
    } else {
        return std::string(entry.level, ' ') + entry.path.filename().string();
    }
}


void FileBrowser::updateListViewElements() {

    removeAllElements();

    for (const auto& entry : fileEntries) {
        addElement(buildEntryName(entry));
    }
}


std::vector<FileBrowser::FileTreeEntry> FileBrowser::getRootDirectories() const {

    std::vector<FileTreeEntry> rootEntries;

    DWORD drives = GetLogicalDrives();
    for (char letter = 'A'; letter <= 'Z'; letter++) {

        if (drives & (1 << (letter - 'A'))) {
            const std::string driveName = std::string(1, letter) + ":/";
            rootEntries.emplace_back(driveName,
                                     0,
                                     DirEntryType::DRIVE,
                                     FileType::NOT_A_FILE,
                                     letter);
        }
    }

    return rootEntries;
}


std::vector<FileBrowser::FileTreeEntry> FileBrowser::getDirectoryEntries(const std::filesystem::path& path) const {

    std::vector<FileTreeEntry> entries;

    for (const auto& entry : std::filesystem::directory_iterator(path)) {

        entries.emplace_back(getFileTreeEntry(entry));
    }

    return entries;
}


FileBrowser::FileTreeEntry FileBrowser::getFileTreeEntry(const std::filesystem::directory_entry& entry) const {

    const auto& path = entry.path();

    return FileTreeEntry {
        .path      = path,
        .level     = getDirectoryDepth(path),
        .entryType = DirEntryType::FILE,
        .fileType  = FileType::NOT_A_FILE
    };
}


u32 FileBrowser::getDirectoryDepth(const std::filesystem::path& path) const {

    return static_cast<u32>(std::distance(path.begin(), path.end()) - 2);
}


std::filesystem::path FileBrowser::getCurrentPath() const {

    return fileEntries.at(currentDirDepth).path.parent_path();
}


const FileBrowser::FileTreeEntry& FileBrowser::getCurrentSelectedElement() const {

    return fileEntries.at(getCursorPosition());
}
