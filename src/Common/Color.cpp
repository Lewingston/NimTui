
#include "Color.h"

using namespace TUI;

const Color Color::TRANSP { 0, 0, 0, 0 };

const Color Color::WHITE  { 255, 255, 255 };
const Color Color::BLACK  {   0,   0,   0 };
const Color Color::RED    { 255,   0,   0 };
const Color Color::GREEN  {   0, 255,   0 };
const Color Color::BLUE   {   0,   0, 255 };
const Color Color::YELLOW { 255, 255,   0 };
const Color Color::ORANGE { 255, 128,   0 };
const Color Color::PURPLE { 128,   0, 128 };
const Color Color::GRAY   { 128, 128, 128 };


Color Color::overlay(Color color) const noexcept {

    return color.multAlpha(color.a).add(this->multAlpha((255 - color.a)));
}


Color Color::multAlpha(u8 alpha) const noexcept {

    const f32 fa = static_cast<f32>(alpha) / 255.0f;

    return Color(
        static_cast<u8>(static_cast<f32>(r) * fa),
        static_cast<u8>(static_cast<f32>(g) * fa),
        static_cast<u8>(static_cast<f32>(b) * fa)
    );
}


Color Color::add(Color color) const noexcept {

    return Color(
        r + color.r,
        g + color.g,
        b + color.b
    );
}
