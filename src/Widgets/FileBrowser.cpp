
#include "FileBrowser.h"

#include <filesystem>

#include <windows.h>

using namespace TUI;


FileBrowser::FileBrowser(Vec2<s32> pos, Vec2<u32> size) :
    ListView(pos, size) {

    addElements(getRootDirectories());
}


std::string FileBrowser::enter() {

    const std::string path = getCurrentSelectedPath();
    const std::filesystem::path fsPath = path;

    if (std::filesystem::is_directory(fsPath))
        update(path);

    return path;
}


std::string FileBrowser::leave() {

    if (currentDirDepth == 0)
        return getCurrentSelectedPath();

    currentDirDepth -= 1;
    if (currentDirDepth == 0) {

        removeAllElements();
        addElements(getRootDirectories());
        return "";

    } else {

        update(getCurrentPath());

        return getCurrentPath();
    }
}


void FileBrowser::update(const std::string& path) {

    const std::filesystem::path fsPath(path);

    if (!std::filesystem::exists(fsPath))
        return;

    if (!std::filesystem::is_directory(fsPath)) {

    }

    std::vector<std::string> list;

    for (const auto& dir : fsPath) {
        if (!dir.string().empty() && dir.string() != "/")
            list.push_back(dir.string() + "/");
    }

    currentDirDepth = static_cast<u32>(list.size());

    const std::vector<std::string> entries = getDirectoryEntries(path);
    list.insert(list.end(), entries.begin(), entries.end());

    removeAllElements();
    addElements(list);
}


std::vector<std::string> FileBrowser::getRootDirectories() const {

    std::vector<std::string> driveNames;

    DWORD drives = GetLogicalDrives();
    for (char letter = 'A'; letter <= 'Z'; letter++) {

        if (drives & (1 << (letter - 'A'))) {
            const std::string driveName = std::string(1, letter) + ":/";
            driveNames.push_back(driveName);
        }
    }

    return driveNames;
}


std::vector<std::string> FileBrowser::getDirectoryEntries(const std::string& path) const {

    std::vector<std::string> entries;

    const std::filesystem::path fsPath = path;
    for (const auto& entry : std::filesystem::directory_iterator(fsPath)) {

        entries.push_back(entry.path().filename().string());
    }

    return entries;
}


std::string FileBrowser::getCurrentPath(u32 depthLimit) const {

    std::string path;

    for (u32 ii = 0; ii < currentDirDepth && ii < depthLimit; ii++) {

        path += getElementAt(ii);
    }

    return path;
}


std::string FileBrowser::getCurrentSelectedPath() const {

    std::string path = getCurrentPath(getCursorPosition());

    path += getSelectedElement();

    return path;
}
