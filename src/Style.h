#pragma once

#include "Color.h"

namespace TUI {

    struct Style {

        struct Text {

            struct Selected {

                Color color;
                Color backgroundColor;
            };

            Color color;
            Color backgroundColor;

            Selected selected;
        };

        Color primaryBackColor;
        Color secondaryBackColor;
        Color borderColor;
        Text text;
    };

    static constexpr Style DEFAULT_STYLE = {

        .primaryBackColor        = Color(255, 255, 255),
        .secondaryBackColor      = Color(32, 32, 32),
        .borderColor             = Color(0, 0, 0),
        .text = {
            .color               = Color(0, 0, 0),
            .backgroundColor     = Color(255, 255, 255),
            .selected = {
                .color           = Color(255, 255, 255),
                .backgroundColor = Color(0, 0, 0)
            }
        }
    };
}
