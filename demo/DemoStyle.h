#pragma once

#include "Style.h"

namespace TUI {

    static constexpr Style DEMO_STYLE = {

        .backgroundColor         = Color(0x060a1dff),
        .borderElementColor      = Color(0x112240ff),
        .text = {
            .color               = Color(0xac720fff),
            .backgroundColor     = Color(0x060a1dff),
            .selected = {
                .color           = Color(0x060a1dff),
                .backgroundColor = Color(0xac720fff)
            }
        }
    };
}
