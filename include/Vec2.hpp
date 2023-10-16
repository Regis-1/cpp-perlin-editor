#pragma once

template<typename T>
struct Vec2 {
    Vec2();
    Vec2(T x, T y) : x(x), y(y) {}
    ~Vec2(){}

    float Length();
    Vec2<T> operator+(Vec2<T> const& other) {
        return {(x + other.x), (y + other.y)};
    }
    Vec2<T> operator-(Vec2<T> const& other) {
        return {(x - other.x), (y - other.y)};
    }
    Vec2<T> operator*(T const scalar) {
        return {x * scalar, y * scalar};
    }
    Vec2<T>& operator*=(T const scalar) {
        x *= scalar; y *= scalar;
        return *this;
    }
    Vec2<T> operator*(Vec2<T> const& other) {
        return {(x * other.x), (y * other.y)};
    }

    T x;
    T y;
};
