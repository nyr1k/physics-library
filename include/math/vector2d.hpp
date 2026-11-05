#pragma once

#include <concepts>
#include <cmath>
#include <cassert>
#include <type_traits>


namespace physm::vec {

    template <typename T>
    concept AllowedTypes = std::same_as<int, T> || std::same_as<float, T>;


    template <AllowedTypes T>
    class Vector2 {
    public:
        T x;
        T y;

        Vector2() : x(0), y(0) {}

        Vector2(const T x, const T y) : x(x), y(y) {}

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
        bool equal_float(float x1, float y1, float x2, float y2, float epsilon = 1e-6f) const
        {
            return (std::abs(x1-x2) < epsilon && std::abs(y1-y2) < epsilon);
        }
    };

    using vec2 = Vector2<float>;
    using vec2i = Vector2<int>;
}

