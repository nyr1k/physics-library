#pragma once

#include <concepts>
#include <array>
#include <type_traits>
#include <cmath>
#include <cstddef>

#include "vector2d.hpp"


namespace physm {

template <typename T>
concept AllowedTypesMatrix = std::same_as<T, float> || std::same_as<T, int>;

template <AllowedTypesMatrix T>
class Matrix2 {
    private:
        std::array<T, 4> matrix; 

    public:
        constexpr Matrix2() : matrix{} {}
        constexpr Matrix2(const T val) : matrix{val, val, val, val} {}

        /*Change the third argument to false, 
            if you want to append  vectors as columns*/
        constexpr Matrix2(const physm::Vector2<T>& v1, const physm::Vector2<T>& v2, bool ConstructAsRows = true) 
        {
            if (ConstructAsRows)
                matrix = {v1.x, v1.y, v2.x, v2.y};
            else
                matrix = {v1.x, v2.x, v1.y, v2.y};
        }

        //matrix[row][col] = val
        T* operator[](size_t row)
        {
            return &matrix[row*2];
        }

        //val = matrix[row][col]
        const T* operator[](size_t row) const
        {
            return &matrix[row*2];
        }

        //Matrix addition
        Matrix2 operator+(const Matrix2& add_mat) const
        {
            return Matrix2(
                physm::Vector2<T>(
                    matrix[0]+add_mat[0][0],
                    matrix[1]+add_mat[0][1]
                ),
                physm::Vector2<T>(
                    matrix[2]+add_mat[1][0],
                    matrix[3]+add_mat[1][1]
                )
            );
        }

        //Matrix subtraction
        Matrix2 operator-(const Matrix2& sub_mat) const
        {
            return Matrix2(
                physm::Vector2<T>(
                    matrix[0]-sub_mat[0][0],
                    matrix[1]-sub_mat[0][1]
                ),
                physm::Vector2<T>(
                    matrix[2]-sub_mat[1][0],
                    matrix[3]-sub_mat[1][1]
                )
            );
        }

        //Matrix Matrix multiplication
        Matrix2 operator*(const Matrix2& mult_mat) const
        {
            return Matrix2(
                physm::Vector2<T>(
                    matrix[0]*mult_mat[0][0] + matrix[1]*mult_mat[1][0],
                    matrix[0]*mult_mat[0][1] + matrix[1]*mult_mat[1][1]
                ),
                physm::Vector2<T>(
                    matrix[2]*mult_mat[0][0] + matrix[3]*mult_mat[1][0],
                    matrix[2]*mult_mat[0][1] + matrix[3]*mult_mat[1][1]
                )
            );
        }

        //Matrix Vector multiplication
        physm::Vector2<T> operator*(const physm::Vector2<T>& mult_vec) const
        {
            return physm::Vector2<T>(
                    matrix[0]*mult_vec.x + matrix[1]*mult_vec.y, // x
                    matrix[2]*mult_vec.x + matrix[3]*mult_vec.y // y
            );
        }

        //Compound scalar multiplication
        Matrix2& operator*=(const T val) 
        {
            matrix[0] *= val;
            matrix[1] *= val;
            matrix[2] *= val;
            matrix[3] *= val;
        
            return *this;
        }

        //Scalar multiplication (Scalar is on the right)
        Matrix2 operator*(const T val) const
        {
            Matrix2 mat = *this;
            mat *= val;
            return mat;
        }

        //Scalar multiplication (Scalar is on the left)
        friend Matrix2 operator*(const T val, const Matrix2& mat) 
        {
            return mat*val;
        }

        /*Compound scalar division
            Scalar should not be zero */
        Matrix2& operator/=(const T val) 
        {
            matrix[0] /= val;
            matrix[1] /= val;
            matrix[2] /= val;
            matrix[3] /= val;
        
            return *this;
        }

        /*Scalar division (Scalar is on the right)
            Scalar should not be zero */
        Matrix2 operator/(const T val) const
        {
            Matrix2 mat = *this;
            mat /= val;
            return mat;
        }

        bool operator==(const Matrix2& mat) const
        {
            if constexpr (std::is_floating_point_v<T>) 
                return equal_float(mat);
            else
                return equal_int(mat);
        }

        //Determinant
        constexpr T det() const
        {
            return matrix[0]*matrix[3] - matrix[1]*matrix[2]; //ad-cb
        } 

        //Transpose
        constexpr Matrix2 trans() const 
        {
            return Matrix2(
                physm::Vector2<T>(matrix[0], matrix[2]),
                physm::Vector2<T>(matrix[1], matrix[3])
            );
        }        

        //Inverse is allowed for float Matrices only
        template <typename U = T>
        requires std::same_as<U, float> && std::same_as<U, T>   
        constexpr Matrix2 inverse() const
        {
            float inv_det = 1.0f/this->det();
            return Matrix2(
                physm::Vector2<float>(matrix[3]*inv_det, (-matrix[1])*inv_det),
                physm::Vector2<float>((-matrix[2])*inv_det, matrix[0]*inv_det)
            );
        }

        //Return an Identity Matrix
        static constexpr Matrix2 identity()
        {
            return Matrix2(
                Vector2<T>{T{1}, T{0}},
                Vector2<T>{T{0}, T{1}}
            );
        }

        /*Set a different epsilon for equality check (default = 1e-6f)
            Works only for Matrix2<float> */
        static void set_epsilon(float new_epsilon)
        {
            epsilon = new_epsilon;
        }

    private:
        static inline float epsilon = 1e-6f;

        bool equal_float(const Matrix2& m2) const
        {
            auto is_equal = [](T a, T b) 
            {
                if (std::abs(a-b) < epsilon)
                    return true;
                
                T max_val = std::max(std::abs(a), std::abs(b));
                return std::abs(a-b) < epsilon*max_val;
            };

            return (is_equal(matrix[0], m2[0][0]) &&
                    is_equal(matrix[1], m2[0][1]) &&
                    is_equal(matrix[2], m2[1][0]) &&
                    is_equal(matrix[3], m2[1][1]));
        }

        bool equal_int(const Matrix2& m2) const
        {
            return (matrix[0] == m2[0][0] &&
                    matrix[1] == m2[0][1] &&
                    matrix[2] == m2[1][0] &&
                    matrix[3] == m2[1][1]);
        }
};

using mat2f = Matrix2<float>;
using mat2i = Matrix2<int>;
}