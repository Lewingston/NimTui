#pragma once

#include "Style.h"

namespace TUI {

    static constexpr Color primaryBackColor   = Color(0x050919ff);
    static constexpr Color secondaryBackColor = Color(0x080D26ff);
    static constexpr Color borderColor        = Color(0x112240ff);
    static constexpr Color textColor          = Color(0xbc7d10ff);

    static constexpr Style DEMO_STYLE = {

        .primaryBackColor        = primaryBackColor,
        .secondaryBackColor      = secondaryBackColor,
        .borderColor             = borderColor,
        .text = {
            .color               = textColor,
            .backgroundColor     = Color(0),
            .selected = {
                .color           = primaryBackColor,
                .backgroundColor = textColor
            }
        }
    };
}
