
#include "Types.h"
#include "ConsoleWindow.h"
#include "Image.h"
#include "FileTree.h"
#include "ImageView.h"

#include "Console/Console.h"
#include "Console/ConsoleWindow.h"
#include "Console/ConsoleSequences.h"
#include "Console/RenderBuffer.h"

#include "Primitives/Text.h"

#include "Widgets/Grid.h"
#include "Widgets/ListView.h"
#include "Widgets/FileBrowser.h"
#include "Widgets/TextBox.h"

#include <random>
#include <filesystem>
#include <iostream>

#include <windows.h>

using namespace TUI;

std::random_device randomDevice;
std::mt19937 gen(randomDevice());


void fileSelected(FileTree& fileTree, ImageView& imageView) {

    const std::string path = fileTree.enter();
    const std::filesystem::path fsPath = path;

    if (std::filesystem::is_regular_file(fsPath)) {

        std::string extension = fsPath.extension().string();
        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

        if (extension == ".png" ||
            extension == ".jpg" ||
            extension == ".jpeg") {

            imageView.loadImage(path);
        }
    }
}


int main() {

    ConsoleWindow window;

    window.show();

    Grid grid({0, 0}, window.getSize());
    grid.setColors({26, 33, 46}, {33, 40, 59});
    grid.setTextColor({ 100, 114, 137 });
    grid.setGridSize({ 24, 12 });
    grid.enableNumbers(true);

    ListView listView({15, 5}, {60, 10});
    listView.addElement("Test 1");
    listView.addElement("Test 2");
    listView.addElement("Test 3");
    listView.addElement("Bla bla bla");
    listView.addElement("Add a very long entry to the list, to see if the entry is wider than the list it self an a");
    listView.addElement("Short entry");
    //listView.enableWrapAround(false);

    FileBrowser fileBrowser({15, 20}, {60, 15});

    TextBox textBox({0, 0}, {0, 0});
    textBox.setPos({0, static_cast<s32>(window.getSize().getHeight()) - 5});
    textBox.setSize({window.getSize().getWidth(), 5});
    textBox.setText("Text Box\nFor debug info!");
    textBox.setBackColor({33, 40, 59});

    for (u32 ii = 0; ii < 50; ii++) {
        listView.addElement("Entry - " + std::to_string(ii));
    }

    bool terminate = false;

    window.onResize([&]() {

        grid.setSize(window.getSize());

        textBox.setPos({0, static_cast<s32>(window.getSize().getHeight() - 5)});
        textBox.setSize({window.getSize().getWidth(), 5});
    });

    window.onKeyInput([&](Console::KeyEvent keyEvent) {

        if (!keyEvent.pressed)
            return;

        if (keyEvent.keyCode == KeyCode::K) {
            fileBrowser.moveCursor(-1);
        } else if (keyEvent.keyCode == KeyCode::J) {
            fileBrowser.moveCursor(1);
        } else if (keyEvent.keyCode == KeyCode::ESC) {
            terminate = true;
        } else if (keyEvent.keyCode == KeyCode::ENTER) {
            const std::string path = fileBrowser.enter();
            textBox.setText(path);
        } else if (keyEvent.keyCode == KeyCode::MINUS) {
            const std::string path = fileBrowser.leave();
            textBox.setText(path);
        } else {
            textBox.setText(std::format("{:x}", static_cast<u32>(keyEvent.keyCode)));
            //std::cout << std::hex << static_cast<u32>(keyEvent.keyCode) << '\n';
        }
    });

    while (!terminate) {

        window.readConsoleInput();

        auto renderBuffer = window.getRenderBuffer().lock();
        grid.draw(*renderBuffer, {0, 0});
        listView.draw(*renderBuffer, {0, 0});
        fileBrowser.draw(*renderBuffer, {0, 0});
        textBox.draw(*renderBuffer, {0 ,0});

        auto seq = renderBuffer->createTerminalSequence();
        std::cout << seq;
    }

    /*
    SetConsoleOutputCP(CP_UTF8);

    ConsoleWindow window;
    RenderBuffer& buffer = window.getRenderBuffer();
    const Vec2<u32> winSize = buffer.getSize();
    */

    /*
    std::cout << "Window size: " << winSize.getWidth() << " / " << winSize.getHeight() << '\n';
    std::cout << "Press key to continue...\n";
    std::cout << "sizeof char: " << sizeof(char) << '\n';

    Image image2 = Image::loadFromFile("D:/bilder/darwin.jpg");
    Image image = image2.scaleToSize(winSize);
    */

    /*
    const u32 fileTreeWidth = static_cast<u32>(static_cast<float>(winSize.getWidth()) * 0.15f);
    const u32 imageViewWidth = winSize.getWidth() - fileTreeWidth;

    FileTree fileTree({0, 0}, { fileTreeWidth, winSize.getHeight()});
    ImageView imageView({static_cast<s32>(fileTreeWidth), 0}, {imageViewWidth, winSize.getHeight()});

    fileTree.setBorderColor(Color::RED);
    imageView.setBorderColor(Color::BLUE);

    window.show();

    while (true) {

        fileTree.blit(buffer, {0, 0});
        imageView.blit(buffer, {0, 0});

        window.flip();

        s32 input = _getwch();
        if (input == 'k')
            fileTree.moveCursor(-1);
        else if (input == 'j')
            fileTree.moveCursor(1);
        else if (input == '-')
            fileTree.leave();
        else if (input == 13)
            fileSelected(fileTree, imageView);
        else if (input == 27) {
            if (imageView.getImage().isValid()) {
                Image image;
                imageView.setImage(image);
            } else {
                break;
            }
        }
    }

    window.hide();
    */

    return 0;
}
