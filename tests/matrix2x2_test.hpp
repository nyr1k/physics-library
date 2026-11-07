#include <iostream>
#include <cassert>
#include <cmath>
#include <concepts>

#include <math/matrix2x2.hpp> // Adjust path if needed

void matrix_constructors_and_access()
{
    // Default constructor (zero-initialized)
    physm::mat2i m_zero;
    assert(m_zero[0][0] == 0 && m_zero[0][1] == 0);
    assert(m_zero[1][0] == 0 && m_zero[1][1] == 0);

    // Single value constructor
    physm::mat2f m_val(3.5f);
    assert(m_val[0][0] == 3.5f && m_val[0][1] == 3.5f);
    assert(m_val[1][0] == 3.5f && m_val[1][1] == 3.5f);

    // Vector constructor (as rows - default)
    physm::Vector2<int> r1(1, 2);
    physm::Vector2<int> r2(3, 4);
    physm::mat2i m_rows(r1, r2, true);
    assert(m_rows[0][0] == 1 && m_rows[0][1] == 2);
    assert(m_rows[1][0] == 3 && m_rows[1][1] == 4);

    // Vector constructor (as columns)
    physm::mat2i m_cols(r1, r2, false);
    assert(m_cols[0][0] == 1 && m_cols[0][1] == 3);
    assert(m_cols[1][0] == 2 && m_cols[1][1] == 4);

    // Mutation via operator[]
    m_cols[0][1] = 99;
    assert(m_cols[0][1] == 99);

    // Const access via operator[]
    const physm::mat2i m_const = m_rows;
    assert(m_const[1][0] == 3);

    // Identity matrix
    physm::mat2f id = physm::mat2f::identity();
    assert(id[0][0] == 1.0f && id[0][1] == 0.0f);
    assert(id[1][0] == 0.0f && id[1][1] == 1.0f);
}

void matrix_addition_and_subtraction()
{
    physm::mat2i a({1, 2}, {3, 4});
    physm::mat2i b({5, 6}, {7, 8});

    physm::mat2i sum = a + b;
    assert(sum == physm::mat2i({6, 8}, {10, 12}));

    physm::mat2i diff = b - a;
    assert(diff == physm::mat2i({4, 4}, {4, 4}));

    physm::mat2f af({1.5f, -2.5f}, {3.0f, 4.25f});
    physm::mat2f bf({0.5f, 2.5f}, {-1.0f, 0.75f});

    assert((af + bf) == physm::mat2f({2.0f, 0.0f}, {2.0f, 5.0f}));
    assert((af - bf) == physm::mat2f({1.0f, -5.0f}, {4.0f, 3.5f}));
}

void matrix_scalar_operations()
{
    physm::mat2i m({2, -4}, {6, 8});

    // Right scalar multiplication
    physm::mat2i r_mult = m * 3;
    assert(r_mult == physm::mat2i({6, -12}, {18, 24}));

    // Left scalar multiplication (friend function)
    physm::mat2i l_mult = 3 * m;
    assert(l_mult == physm::mat2i({6, -12}, {18, 24}));

    // Compound scalar multiplication
    physm::mat2i c_mult = m;
    c_mult *= -2;
    assert(c_mult == physm::mat2i({-4, 8}, {-12, -16}));

    // Scalar division & compound scalar division
    physm::mat2f mf({10.0f, -20.0f}, {30.0f, 40.0f});
    assert((mf / 10.0f) == physm::mat2f({1.0f, -2.0f}, {3.0f, 4.0f}));

    mf /= 2.0f;
    assert(mf == physm::mat2f({5.0f, -10.0f}, {15.0f, 20.0f}));
}

void matrix_multiplication_and_vector()
{
    physm::mat2i a({1, 2}, {3, 4});
    physm::mat2i b({2, 0}, {1, 2});

    // A * B = [1*2+2*1, 1*0+2*2; 3*2+4*1, 3*0+4*2] = [4, 4; 10, 8]
    physm::mat2i ab = a * b;
    assert(ab == physm::mat2i({4, 4}, {10, 8}));

    // B * A = [2*1+0*3, 2*2+0*4; 1*1+2*3, 1*2+2*4] = [2, 4; 7, 10]
    physm::mat2i ba = b * a;
    assert(ba == physm::mat2i({2, 4}, {7, 10}));
    assert(!(ab == ba)); // Verify non-commutativity

    // Matrix * Identity == Matrix
    physm::mat2f f({3.5f, -1.2f}, {0.0f, 7.8f});
    assert((f * physm::mat2f::identity()) == f);

    // Matrix * Vector
    physm::Vector2<int> v(3, 5);
    physm::Vector2<int> mv = a * v; // [1*3 + 2*5, 3*3 + 4*5] = (13, 29)
    assert(mv.x == 13 && mv.y == 29);
}

void matrix_linear_algebra()
{
    // Determinant
    physm::mat2i mi({3, 8}, {4, 6});
    assert(mi.det() == -14); // 3*6 - 8*4 = 18 - 32 = -14

    // Transpose
    physm::mat2i mt = mi.trans();
    assert(mt == physm::mat2i({3, 4}, {8, 6}));
    assert(mt.trans() == mi);

    // Inverse (float only)
    physm::mat2f mf({4.0f, 7.0f}, {2.0f, 6.0f});
    assert(std::abs(mf.det() - 10.0f) < 1e-6f);

    physm::mat2f inv = mf.inverse();
    // Expected inverse: 1/10 * [6, -7; -2, 4] = [0.6, -0.7; -0.2, 0.4]
    assert(inv == physm::mat2f({0.6f, -0.7f}, {-0.2f, 0.4f}));

    // M * M^-1 == Identity
    assert((mf * inv) == physm::mat2f::identity());
    assert((inv * mf) == physm::mat2f::identity());


}

void matrix_equality_and_epsilon()
{
    physm::mat2f a({1.0f, 2.0f}, {3.0f, 4.0f});
    physm::mat2f b({1.0f + 1e-7f, 2.0f}, {3.0f, 4.0f - 1e-7f});

    // Should be equal under default epsilon (1e-6f)
    assert(a == b);

    // Tighten epsilon and verify they are no longer considered equal
    physm::mat2f::set_epsilon(1e-9f);
    assert(!(a == b));

    // Reset epsilon back to default
    physm::mat2f::set_epsilon(1e-6f);
    assert(a == b);
}

