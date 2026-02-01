
#include "FileTree.h"
#include "ConsoleWindow.h"

#include <algorithm>
#include <filesystem>

#include <windows.h>

using namespace TUI;


FileTree::FileTree(Vec2<s32> pos, Vec2<u32> size) :
    Widget(pos, size) {

    currentDir = getRootDirectories();
}


void FileTree::draw(RenderBuffer& buffer, Vec2<s32> offset) {

    Widget::draw(buffer, offset);

    offset = Vec2<s32>(offset.getX() + getPos().getX(), offset.getY() + getPos().getY());

    /*
    if (showBorder())
        offset = Vec2<s32>(offset.getX() + 1, offset.getY() + 1);
    */

    drawCursor(buffer, offset);
    drawTree(buffer, offset);

    const s32 depth = static_cast<s32>(currentBranch.size());
    offset = Vec2<s32>(offset.getX() + depth * 2, offset.getY() + depth);

    drawCurrentDir(buffer, offset);
}


void FileTree::moveCursor(s32 move) {

    currentPos = std::clamp(
        static_cast<u32>(static_cast<s32>(currentPos) + move),
        0u,
        static_cast<u32>(currentDir.size())
    );
}


std::string FileTree::enter() {

    const std::string path = getCurrentSelectedPath();
    const std::filesystem::path fsPath = path;

    if (std::filesystem::is_directory(fsPath)) {

        // Enter directory
        currentBranch.push_back(currentDir.at(currentPos));
        currentDir = getDirectoryEntries(getCurrentPath());

        currentPos = 0;
    }

    return path;
}


std::string FileTree::leave() {

    currentBranch.pop_back();
    currentPos = 0;

    if (currentBranch.empty()) {
        currentDir = getRootDirectories();
        return getCurrentSelectedPath();
    }

    std::string path = getCurrentPath();
    currentDir = getDirectoryEntries(path);

    return path;
}


void FileTree::drawTree(RenderBuffer& buffer, Vec2<s32> offset) {

    for (s32 ii = 0; ii < currentBranch.size(); ii++) {

        const Vec2<s32> currentPos(offset.getX() + ii * 2, offset.getY() + ii);
        //buffer.print(currentPos, currentBranch.at(ii), textColor);
    }
}


void FileTree::drawCurrentDir(RenderBuffer& buffer, Vec2<s32> offset) {

    for (s32 ii = 0; ii < currentDir.size(); ii++) {

        const Vec2<s32> currentPos(offset.getX(), offset.getY() + ii);
        //buffer.print(currentPos, currentDir.at(ii), textColor);
    }
}


void FileTree::drawCursor(RenderBuffer& buffer, Vec2<s32> offset) {

    s32 width = static_cast<s32>(getSize().getWidth());
    s32 start = 0;

    /*
    if (showBorder()) {
        width -= 2;
        start += 1;
    }
    */

    for (s32 ii = start; ii < width; ii++) {

        Vec2<u32> pos(offset.getX() + ii, offset.getY() + currentPos + currentBranch.size());
        //buffer.set(pos, " ", markColor, textColor);
    }
}


std::vector<std::string> FileTree::getRootDirectories() const {

    std::vector<std::string> driveNames;

    DWORD drives = GetLogicalDrives();
    for (char letter = 'A'; letter <= 'Z'; letter++) {

        if (drives & (1 << (letter - 'A'))) {
          driveNames.push_back(std::string(1, letter));
        }
    }

    return driveNames;
}


std::vector<std::string> FileTree::getDirectoryEntries(const std::string& path) const {

    std::vector<std::string> entries;

    const std::filesystem::path fsPath = path;
    for (const auto& entry : std::filesystem::directory_iterator(fsPath)) {

        entries.push_back(entry.path().filename().string());
    }

    return entries;
}


std::string FileTree::getCurrentPath() const {

    std::string path;

    for (u32 ii = 0; ii < currentBranch.size(); ii++) {

        path += currentBranch.at(ii);
        if (ii == 0)
            path += ":";
        path += "/";
    }

    return path;
}


std::string FileTree::getCurrentSelectedPath() const {

    std::string path = getCurrentPath();

    path += currentDir.at(currentPos);

    if (currentBranch.empty())
        path += ":/";

    return path;
}
