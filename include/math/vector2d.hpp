#pragma once

#include <concepts>
#include <cmath>
#include <cassert>
#include <type_traits>


namespace physm {

template <typename T>
concept AllowedTypesVector = std::same_as<T, float> || std::same_as<T, int>;

template <AllowedTypesVector T>
class Vector2 {
public:
    T x;
    T y;

    constexpr Vector2() : x(0), y(0) {}

    constexpr Vector2(const T x, const T y) : x(x), y(y) {}

    //Adds two vectors 
    Vector2 operator+(const Vector2& add_vec) const 
    {
        return Vector2(x + add_vec.x, y + add_vec.y);
    }

    //Subtracts two vectors
    Vector2 operator-(const Vector2& sub_vec) const
    {
        return Vector2(x - sub_vec.x, y - sub_vec.y);
    }

    //Compound addition of two vectors
    Vector2& operator+=(const Vector2& add_vec) 
    {
        x += add_vec.x;
        y += add_vec.y;

        return *this;
    }

    //Compound subtraction of two vectors
    Vector2& operator-=(const Vector2& sub_vec)
    {
        x -= sub_vec.x;
        y -= sub_vec.y;

        return *this;
    }

    //Multiplies vector by a scalar
    Vector2 operator*(const T scalar) const
    {
        return Vector2(x * scalar, y * scalar);
    }

    /*Divides vector by a scalar.
        Scalar should not be equal to zero.*/
    Vector2 operator/(const T scalar) const
    {
        assert(scalar != T{0});
        return Vector2(x / scalar, y / scalar);
    }

    // Unary negation
    Vector2 operator-() const
    {
        return Vector2(-x, -y);
    }

    // Equality 
    bool operator==(const Vector2& vec) const
    {
        if constexpr (std::is_floating_point_v<T>) 
            return equal_float(vec.x, vec.y);
        else
            return (x == vec.x && y == vec.y);
    }

    //Calculates length of a vector
    float length() const
    {
        float x_f = static_cast<float>(x);
        float y_f = static_cast<float>(y);
        return std::sqrt(x_f*x_f + y_f*y_f);
    }

    //Calculates length squared
    float length_squared() const 
    {
        float x_f = static_cast<float>(x);
        float y_f = static_cast<float>(y);
        return x_f*x_f + y_f*y_f;
    }

    /*The normalization of Vector2<int> result in Vector2<float> always. 
        The vector should not be equal to zero, since the unit vector will be undefined.*/
    friend Vector2<float> normalize(const Vector2<T>& vector)  
    {
        float len = vector.length();
        assert(len != T{0});
        return Vector2<float>(
            static_cast<float>(vector.x)/len, 
            static_cast<float>(vector.y)/len);
    }

    //Performs dot product
    friend T dot(const Vector2& v1, const Vector2& v2)
    {
        return (v1.x * v2.x) + (v1.y * v2.y);
    }

    //Performs cross product
    friend T cross(const Vector2& v1, const Vector2& v2)
    {
        return (v1.x*v2.y) - (v1.y*v2.x);
    }

private:
    static inline float epsilon = 1e-6f;

    bool equal_float(const T x2, const T y2) const
    {
        if (std::abs(x-x2) < epsilon && std::abs(y-y2) < epsilon)
            return true;
        T max_val_x = std::max(std::abs(x), std::abs(x2));
        T max_val_y = std::max(std::abs(y), std::abs(y2));
        return (std::abs(x-x2) < epsilon*max_val_x && std::abs(y-y2) < epsilon*max_val_y);
    }
};

using vec2f = Vector2<float>;
using vec2i = Vector2<int>;
}

