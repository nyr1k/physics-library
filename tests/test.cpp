#include "matrix2x2_test.hpp"
#include "vector2d_test.hpp"

int main()
{
    vector_addition();
    vector_subtraction();
    vector_mult_scalar();
    vector_div_scalar();
    vector_neg();
    vector_equal();
    vector_length();
    vector_squared_length();
    vector_normalize();
    vector_dot();
    vector_cross();

    std::cout << "All Vector2 tests passed successfully!\n";

    matrix_constructors_and_access();
    matrix_addition_and_subtraction();
    matrix_scalar_operations();
    matrix_multiplication_and_vector();
    matrix_linear_algebra();
    matrix_equality_and_epsilon();

    std::cout << "All Matrix2 tests passed successfully!\n";
    return 0;
}