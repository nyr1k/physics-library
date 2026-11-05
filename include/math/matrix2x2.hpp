#pragma once

#include <concepts>
#include <array>

#include "vector2d.hpp"


namespace physm::mat {

    template <typename T>
    concept AllowedTypes = std::same_as<T, int> || std::same_as<T, float>;


    template <AllowedTypes T>
    class Matrix2 {
        private:
            std::array<T, 4> matrix; 

        public:
            Matrix2(const T val) : matrix{val, val, val, val} {}

            /*Change the third argument to false, 
                if you want to append  vectors as columns*/
            Matrix2(const physm::vec::Vector2<T>& v1, const physm::vec::Vector2<T>& v2, bool row = true) 
            {
                if (row)
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
                    physm::vec::Vector2<T>(
                        matrix[0]+add_mat[0][0],
                        matrix[1]+add_mat[0][1]
                    ),
                    physm::vec::Vector2<T>(
                        matrix[2]+add_mat[1][0],
                        matrix[3]+add_mat[1][1]
                    )
                );
            }

            //Matrix subtraction
            Matrix2 operator-(const Matrix2& add_mat) const
            {
                return Matrix2(
                    physm::vec::Vector2<T>(
                        matrix[0]-add_mat[0][0],
                        matrix[1]-add_mat[0][1]
                    ),
                    physm::vec::Vector2<T>(
                        matrix[2]-add_mat[1][0],
                        matrix[3]-add_mat[1][1]
                    )
                );
            }

            //Matrix multiplication
            Matrix2 operator*(const Matrix2& add_mat) const
            {
                return Matrix2(
                    physm::vec::Vector2<T>(
                        matrix[0]*add_mat[0][0] + matrix[1]*add_mat[1][0],
                        matrix[0]*add_mat[0][1] + matrix[1]*add_mat[1][1]
                    ),
                    physm::vec::Vector2<T>(
                        matrix[2]*add_mat[0][0] + matrix[3]*add_mat[1][0],
                        matrix[2]*add_mat[0][1] + matrix[3]*add_mat[1][1]
                    )
                );
            }
    };

    using mat2 = Matrix2<float>;
    using mat2i = Matrix2<int>;
}