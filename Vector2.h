#pragma once
#include <cmath>
#include <iostream>
template<typename T>
class Vector2 {
public:
    T x, y;
    Vector2(T x, T y) : x(x), y(y){};
    Vector2(){};

    Vector2<T> operator+(Vector2<float>& other) const;
    static double Distance(Vector2<T>& a, Vector2<T>& b);
};