#pragma once

#include <type_traits>
#include <utility>

namespace TUI {

    // Opt-in type trait for bit mask enums

    template<typename E>
    struct enable_bitmask_operators : std::false_type {};

    template<typename E>
    concept bitmask_enum =
        std::is_enum_v<E> &&
        enable_bitmask_operators<E>::value;

    // Generic operators for bit mask enums

    template<bitmask_enum E>
    constexpr E operator| (E lhs, E rhs) {
        return static_cast<E>(std::to_underlying(lhs) | std::to_underlying(rhs));
    }

    template<bitmask_enum E>
    constexpr E operator& (E lhs, E rhs) {
        return static_cast<E>(std::to_underlying(lhs) & std::to_underlying(rhs));
    }

    template<bitmask_enum E>
    constexpr E operator^ (E lhs, E rhs) {
        return static_cast<E>(std::to_underlying(lhs) ^ std::to_underlying(rhs));
    }

    template<bitmask_enum E>
    constexpr E operator~ (E value) {
        return static_cast<E>(~std::to_underlying(value));
    }

    template<bitmask_enum E>
    constexpr E& operator|= (E& lhs, E rhs) {
        return lhs = lhs | rhs;
    }

    template<bitmask_enum E>
    constexpr E& operator&= (E& lhs, E rhs) {
        return lhs = lhs & rhs;
    }

    template<bitmask_enum E>
    constexpr E& operator^= (E& lhs, E rhs) {
        return lhs = lhs ^ rhs;
    }

    // helper function to check if flag ist set

    template<bitmask_enum E>
    constexpr bool hasFlag(E value, E flag) {
        return (value & flag) == flag;
    }
}
