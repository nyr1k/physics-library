#include <concepts>

template <typename T>
concept AllowedTypes = std::same_as<int, T> || std::same_as<float, T>;


template <AllowedTypes T>
class vec2 {
public:
    T x;
    T y;

    vec2() : x(0), y(0) {}
    vec2(const T x, const T y) : x(x), y(y){}

    vec2 operator+(const vec2& add_vec) const 
    {
        return vec2(x + add_vec.x, y + add_vec.y);
    }

    vec2& operator+=(const vec2& add_vec) 
    {
        x += add_vec.x;
        y += add_vec.y;

        return *this;
    }

    vec2 operator*(const T scalar) const
    {
        return vec2(x * scalar, y * scalar);
    }
};