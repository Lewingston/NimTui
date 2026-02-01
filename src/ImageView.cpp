
#include "ImageView.h"

using namespace TUI;


ImageView::ImageView(Vec2<s32> pos, Vec2<u32> size) :
    Widget(pos, size) {

}


void ImageView::draw(RenderBuffer& buffer, Vec2<s32> offset) {

    Widget::draw(buffer, offset);

    image.blit(buffer, offset);
}


void ImageView::loadImage(const std::string& path) {

    image = Image::loadFromFile(path).scaleToSize(getSize());

    s32 posX = getPos().getX();
    s32 posY = getPos().getY();

    if (image.getSize().getWidth() < getSize().getWidth()) {
        posX += (getSize().getWidth() - image.getSize().getWidth()) / 2;
    }
    if (image.getSize().getHeight() < getSize().getHeight()) {
        posY += (getSize().getHeight() - image.getSize().getWidth()) / 2;
    }

    image.setPos(Vec2<s32>(posX, posY));
}
