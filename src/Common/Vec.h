#pragma once

namespace TUI {

    template<typename T>
    class Vec2 {

        public:

            Vec2() = default;
            Vec2(T x, T y) : x(x), y(y) {}

            // Conversion constructor
            template<typename U>
            Vec2(const Vec2<U>& v) :
                x(static_cast<T>(v.getX())),
                y(static_cast<T>(v.getY())) {}

            [[nodiscard]] T getX() const noexcept { return x; }
            [[nodiscard]] T getY() const noexcept { return y; }

            [[nodiscard]] T getWidth()  const noexcept { return x; }
            [[nodiscard]] T getHeight() const noexcept { return y; }

            [[nodiscard]] T getArea() const noexcept { return x * y; }

            Vec2<T>& operator+=(const Vec2<T>& v) {

                x += v.x;
                y += v.y;

                return *this;
            }

        private:

            T x = 0;
            T y = 0;

    };

    template<typename T>
    [[nodiscard]] Vec2<T> operator+(const Vec2<T>& vec1, const Vec2<T>& vec2) {

        return Vec2<T>(vec1.getX() + vec2.getX(), vec1.getY() + vec2.getY());
    }

    template<typename T>
    [[nodiscard]] Vec2<T> operator-(const Vec2<T>& vec1, const Vec2<T>& vec2) {

        return Vec2<T>(vec1.getX() - vec2.getX(), vec1.getY() - vec2.getY());
    }

    template<typename T, typename U>
    [[nodiscard]] Vec2<T> operator*(const Vec2<T>& vec, U mult) {

        return Vec2<T>(vec.getX() * mult, vec.getY() * mult);
    }
}
