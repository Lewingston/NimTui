#pragma once

#include "Style.h"

namespace TUI {

    static constexpr Color primaryBackColor   = Color(26, 33, 46);
    static constexpr Color secondaryBackColor = Color(20, 27, 36);
    static constexpr Color borderColor        = Color(60, 74, 102);
    static constexpr Color textColor          = Color(147, 164, 195);

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
