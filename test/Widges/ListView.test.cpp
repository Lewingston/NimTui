
#include <gtest/gtest.h>

#include "Widgets/ListView.h"

using namespace TUI;


TEST(ListView, Constructor) {

    ListView listView({3, 5}, {6, 8});

    ASSERT_EQ(listView.getSize().getWidth(), 6);
    ASSERT_EQ(listView.getSize().getHeight(), 8);
    ASSERT_EQ(listView.getPos().getX(), 3);
    ASSERT_EQ(listView.getPos().getY(), 5);
}


TEST(ListView, Destructor) {

    // Test deleting destructor (just to be complete)
    ListView* listView = new ListView({0, 0}, {0, 0});
    delete listView;
}


TEST(ListView, addElement) {

    ListView listView({0, 0}, {0, 0});

    listView.addElement("Test Element 1");
    listView.addElement("Test Element 2");
    listView.addElement("Test Element 3");

    EXPECT_EQ(listView.getElementCount(), 3);
    EXPECT_EQ(listView.getCursorPosition(), 0); // Adding elements should not move the cursor

    // Move the cursor add more elements and check again if the position did not move
    listView.moveCursor(2);
    EXPECT_EQ(listView.getCursorPosition(), 2);
    listView.addElement("Test Element 4");
    listView.addElement("Test Element 5");
    EXPECT_EQ(listView.getCursorPosition(), 2);
}


TEST(ListView, removeElement) {

    ListView listView({0, 0}, {0, 0});

    for (u32 ii = 0; ii < 8; ii++)
        listView.addElement("Test Element " + std::to_string(ii + 1));

    ASSERT_EQ(listView.getElementCount(), 8);
    ASSERT_EQ(listView.getCursorPosition(), 0);

    // Remove element from the middle
    listView.removeElement("Test Element 4");
    ASSERT_EQ(listView.getElementCount(), 7);

    const auto& elements = listView.getAllElements();
    ASSERT_EQ(elements.at(2), "Test Element 3");
    ASSERT_EQ(elements.at(3), "Test Element 5");

    // move cursor to the last element
    listView.moveCursorToLastElement();
    ASSERT_EQ(listView.getCursorPosition(), 6);

    // Remove the last element
    listView.removeElement("Test Element 8");
    ASSERT_EQ(listView.getElementCount(), 6);

    // The cursor should be move to the "new" last element
    ASSERT_EQ(listView.getCursorPosition(), 5);
}


TEST(ListView, removeAllElements) {

    ListView listView({0, 0}, {0, 0});

    listView.addElement("Test Element 1");
    listView.addElement("Test Element 2");
    listView.addElement("Test Element 3");

    ASSERT_EQ(listView.getElementCount(), 3);

    listView.removeAllElements();

    ASSERT_EQ(listView.getElementCount(), 0);
}


TEST(ListView, getSelectedElement) {

    ListView listView({0, 0}, {0, 0});

    // Get element from empty list
    ASSERT_EQ(listView.getSelectedElement(), "");

    listView.addElement("Test Element 1");
    listView.addElement("Test Element 2");
    listView.addElement("Test Element 3");
    listView.addElement("Test Element 4");

    ASSERT_EQ(listView.getSelectedElement(), "Test Element 1");

    listView.moveCursor(1);

    ASSERT_EQ(listView.getSelectedElement(), "Test Element 2");
}


TEST(ListView, getAllElements) {

    ListView listView({0, 0}, {0, 0});

    listView.addElement("Test Element 1");
    listView.addElement("An other element");
    listView.addElement("something something");

    const auto& elements = listView.getAllElements();
    ASSERT_EQ(elements.size(), 3);

    ASSERT_EQ(elements.at(0), "Test Element 1");
    ASSERT_EQ(elements.at(1), "An other element");
    ASSERT_EQ(elements.at(2), "something something");
}


TEST(ListView, moveCursor) {

    ListView listView({0, 0}, {0, 0});

    // On initialization the cursor should on position 0
    ASSERT_EQ(listView.getCursorPosition(), 0);

    // when moving the cursor on a list with zero elements the cursor should not move
    listView.moveCursor(5);
    ASSERT_EQ(listView.getCursorPosition(), 0);

    listView.moveCursor(-4);
    ASSERT_EQ(listView.getCursorPosition(), 0);

    listView.moveCursorToLastElement();
    ASSERT_EQ(listView.getCursorPosition(), 0);

    listView.moveCursorToFirstElement();
    ASSERT_EQ(listView.getCursorPosition(), 0);

    for (u32 ii = 0; ii < 10; ii++)
        listView.addElement("Test Element " + std::to_string(ii + 1));

    // Move cursor forwards
    listView.moveCursor(7);
    ASSERT_EQ(listView.getCursorPosition(), 7);

    // Move cursor backwards
    listView.moveCursor(-4);
    ASSERT_EQ(listView.getCursorPosition(), 3);

    // Move cursor forwards over the last element
    listView.moveCursor(12);
    ASSERT_EQ(listView.getCursorPosition(), 5);

    // Move cursor backwards over the first element
    listView.moveCursor(-8);
    ASSERT_EQ(listView.getCursorPosition(), 7);
}
