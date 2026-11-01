#pragma once

#include <concepts>
#include <cmath>
#include <cassert>
#include <type_traits>

template <typename T>
concept AllowedTypes = std::same_as<int, T> || std::same_as<float, T>;


template <AllowedTypes T>
class vec2 {
public:
    T x;
    T y;

    vec2() : x(0), y(0) {}

    vec2(const T x, const T y) : x(x), y(y) {}

    //Adds two vectors 
    vec2 operator+(const vec2& add_vec) const 
    {
        return vec2(x + add_vec.x, y + add_vec.y);
    }

    //Subtracts two vectors
    vec2 operator-(const vec2& sub_vec) const
    {
        return vec2(x - sub_vec.x, y - sub_vec.y);
    }

    //Compound addition of two vectors
    vec2& operator+=(const vec2& add_vec) 
    {
        x += add_vec.x;
        y += add_vec.y;

        return *this;
    }

    //Compound subtraction of two vectors
    vec2& operator-=(const vec2& sub_vec)
    {
        x -= sub_vec.x;
        y -= sub_vec.y;

        return *this;
    }

    //Multiplies vector by a scalar
    vec2 operator*(const T scalar) const
    {
        return vec2(x * scalar, y * scalar);
    }

    /*Divides vector by a scalar.
        Scalar should not be equal to zero.*/
    vec2 operator/(const T scalar) const
    {
        assert(scalar != 0.0f);
        return vec2(x / scalar, y / scalar);
    }

    // Unary negation
    vec2 operator-() const
    {
        return vec2(-x, -y);
    }

    // Equality 
    bool operator==(const vec2& vec) const
    {
        if constexpr (std::is_floating_point_v<T>) 
            return equal_float(x, y, vec.x, vec.y);
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

    /*The normalization of vec2<int> result in vec2<float> always. 
        The vector should not be equal to zero, since the unit vector will be undefined.*/
    friend vec2<float> normalize(const vec2<T>& vector)  
    {
        float len = vector.length();
        assert(len != T{0});
        return vec2<float>(
            static_cast<float>(vector.x)/len, 
            static_cast<float>(vector.y)/len);
    }

    //Performs dot product
    friend T dot(const vec2& v1, const vec2& v2)
    {
        return (v1.x * v2.x) + (v1.y * v2.y);
    }

    //Performs cross product
    friend T cross_prod(const vec2& v1, const vec2& v2)
    {
        return (v1.x*v2.y) - (v1.y*v2.x);
    }

private:
    bool equal_float(float x1, float y1, float x2, float y2, float epsilon = 1e-6f) const
    {
        return (std::abs(x1-x2) < epsilon && std::abs(y1-y2) < epsilon);
    }
};

