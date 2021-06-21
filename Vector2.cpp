#include "Vector2.h"

template<typename T>
static double Vector2<T>::Distance(Vector2<T>& a, Vector2<T>& b)
{
    std::hypot(a.x - b.x, a.y - b.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator+(Vector2<float>& other) const //Adding override
{
    return Vector2<T>(this->x+other.x, this->y+other.y);
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Vector2<T>& vector2) //Logging override
{
    stream << vector2.x << ", " << vector2.y << " ";
    return stream;
}

