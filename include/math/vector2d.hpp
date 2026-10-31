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

    //add two vectors 
    vec2 operator+(const vec2& add_vec) const 
    {
        return vec2(x + add_vec.x, y + add_vec.y);
    }

    //subtract two vectors
    vec2 operator-(const vec2& sub_vec) const
    {
        return vec2(x - sub_vec.x, y - sub_vec.y);
    }

    //compound addition of two vectors
    vec2& operator+=(const vec2& add_vec) 
    {
        x += add_vec.x;
        y += add_vec.y;

        return *this;
    }

    //compound subtraction of two vectors
    vec2& operator-=(const vec2& sub_vec)
    {
        x -= sub_vec.x;
        y -= sub_vec.y;

        return *this;
    }

    //multiply vector by a scalar
    vec2 operator*(const T scalar) const
    {
        return vec2(x * scalar, y * scalar);
    }

    //divide vector by a scalar
    vec2 operator/(const T scalar) const
    {
        return vec2(x / scalar, y / scalar);
    }

    //perform dot product
    friend T dot(const vec2& v1, const vec2& v2)
    {
        return (v1.x * v2.x) + (v1.y * v2.x);
    }
};

