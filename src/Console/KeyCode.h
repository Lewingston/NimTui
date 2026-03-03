
#include "Types.h"
#include "EnumClassBinaryOperators.h"

namespace TUI {

    enum class KeyCode : u8 {

        NONE                = 0x00,
        LEFT_MOUSE_BUTTON   = 0x01,
        RIGHT_MOUSE_BUTTON  = 0x02,
        // 0x03
        MIDDLE_MOUSE_BUTTON = 0x04,
        // 0x05 - 0x07
        BACK_SPACE          = 0x08,
        TAB                 = 0x09,
        // 0x0a - 0x0c
        ENTER               = 0x0d,
        // 0x0e - 0x0f
        SHIFT               = 0x10,
        CTRL                = 0x11,
        ALT                 = 0x12,
        // 0x13 - 0x1a
        ESC                 = 0x1b,
        // 0x1c - 0x1f
        SPACE               = 0x20,
        SCROLL_UP           = 0x21,
        SCROLL_DOWN         = 0x22,
        END                 = 0x23,
        POS1                = 0x24,
        LEFT                = 0x25,
        UP                  = 0x26,
        RIGHT               = 0x27,
        DOWN                = 0x28,
        SELECT              = 0x29,
        PRINT               = 0x2a,
        EXECUTE             = 0x2b,
        SNAPSHOT            = 0x2c,
        INSERT              = 0x2d,
        _DELETE             = 0x2e,
        // 0x1f
        _0                  = 0x30,
        _1                  = 0x31,
        _2                  = 0x32,
        _3                  = 0x33,
        _4                  = 0x34,
        _5                  = 0x35,
        _6                  = 0x36,
        _7                  = 0x37,
        _8                  = 0x38,
        _9                  = 0x39,
        // 0x3a - 0x40
        A                   = 0x41,
        B                   = 0x42,
        C                   = 0x43,
        D                   = 0x44,
        E                   = 0x45,
        F                   = 0x46,
        G                   = 0x47,
        H                   = 0x48,
        I                   = 0x49,
        J                   = 0x4a,
        K                   = 0x4b,
        L                   = 0x4c,
        M                   = 0x4d,
        N                   = 0x4e,
        O                   = 0x4f,
        P                   = 0x50,
        Q                   = 0x51,
        R                   = 0x52,
        S                   = 0x53,
        T                   = 0x54,
        U                   = 0x55,
        V                   = 0x56,
        W                   = 0x57,
        X                   = 0x58,
        Y                   = 0x59,
        Z                   = 0x5a,
        WIN_LEFT            = 0x5b,
        WIN_RIGHT           = 0x5c,
        // 0x5e - 0x5f
        NUM_0               = 0x60,
        NUM_1               = 0x61,
        NUM_2               = 0x62,
        NUM_3               = 0x63,
        NUM_4               = 0x64,
        NUM_5               = 0x65,
        NUM_6               = 0x66,
        NUM_7               = 0x67,
        NUM_8               = 0x68,
        NUM_9               = 0x69,
        NUM_MULT            = 0x6a,
        NUM_ADD             = 0x6b,
        NUM_SUBTRACT        = 0x6d,
        NUM_DECIMAL         = 0x6e,
        NUM_DIVIDE          = 0x6f,
        F1                  = 0x70,
        F2                  = 0x71,
        F3                  = 0x72,
        F4                  = 0x73,
        F5                  = 0x74,
        F6                  = 0x75,
        F7                  = 0x76,
        F8                  = 0x77,
        F9                  = 0x78,
        F10                 = 0x79,
        F11                 = 0x7a,
        F12                 = 0x7b,
        F13                 = 0x7c,
        F14                 = 0x7d,
        F15                 = 0x7e,
        F16                 = 0x7f,
        F17                 = 0x80,
        F18                 = 0x81,
        F19                 = 0x82,
        F20                 = 0x83,
        F21                 = 0x84,
        F22                 = 0x85,
        F23                 = 0x86,
        F24                 = 0x87,

        MINUS               = 0xbd
    };


    enum class KeyModifier : u16 {

        NONE       = 0,
        ALT_RIGHT  = 1 << 1,
        ALT_LFET   = 1 << 2,
        CTRL_RIGHT = 1 << 3,
        CTRL_LEFT  = 1 << 4,
        SHIFT      = 1 << 5,
        NUMLOCK    = 1 << 6,
        SCROLLLOCK = 1 << 7,
        CAPSLOCK   = 1 << 8
    };

    // Enable binary operations for KeyModifier enum
    template<>
    struct enable_bitmask_operators<KeyModifier> : std::true_type {};
}
