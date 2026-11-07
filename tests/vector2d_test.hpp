#include <iostream>
#include <cassert>
#include <limits>

#include <math/vector2d.hpp>

void vector_addition() 
{
    physm::Vector2<int> v1(0, 0);
    physm::Vector2<int> v2(6, 7);
    physm::Vector2<int> res = v1 + v2;
    assert(res.x == 6);
    assert(res.y == 7);

    v1 += v2;
    assert(v1.x == 6);
    assert(v1.y == 7);

    v1 = physm::Vector2<int>(-13, -50);
    v2 = physm::Vector2<int>(20, -123);
    res = v1 + v2;
    assert(res.x == 7);
    assert(res.y == -173);

    v2 += v1;
    assert(v2.x == 7);
    assert(v2.y == -173);

    physm::Vector2<float> v1f(0.0f, 0.0f);
    physm::Vector2<float> v2f(5.0f, 13.5f);
    physm::Vector2<float> res_f = v1f + v2f;
    assert(res_f.x == 5.0f);
    assert(res_f.y == 13.5f);

    v1f += v2f;
    assert(v1f.x == 5.0f);
    assert(v1f.y == 13.5f);

    v1f = physm::Vector2<float>(-6.7f, 51.3f);
    v2f = physm::Vector2<float>(0.0f, 0.0f);
    res_f = v1f + v2f;
    assert(res_f.x == -6.7f);
    assert(res_f.y == 51.3f);

    v2f += v1f;
    assert(v2f.x == -6.7f);
    assert(v2f.y == 51.3f);
}

void vector_subtraction()
{
    physm::Vector2<int> v1(0, 0);
    physm::Vector2<int> v2(6, 7);
    physm::Vector2<int> res = v1 - v2;
    assert(res.x == -6);
    assert(res.y == -7);

    v1 -= v2;
    assert(v1.x == -6);
    assert(v1.y == -7);

    v1 = physm::Vector2<int>(-13, -50);
    v2 = physm::Vector2<int>(20, -123);
    res = v1 - v2;
    assert(res.x == -33);
    assert(res.y == 73);

    v2 -= v1;
    assert(v2.x == 33);
    assert(v2.y == -73);

    physm::Vector2<float> v1f(0.0f, 0.0f);
    physm::Vector2<float> v2f(5.0f, 13.5f);
    physm::Vector2<float> res_f = v1f - v2f;
    assert(res_f.x == -5.0f);
    assert(res_f.y == -13.5f);

    v1f -= v2f;
    assert(v1f.x == -5.0f);
    assert(v1f.y == -13.5f);

    v1f = physm::Vector2<float>(-6.7f, 51.3f);
    v2f = physm::Vector2<float>(3.5f, -0.3f);
    res_f = v1f - v2f;
    assert(res_f.x == -10.2f);
    assert(res_f.y == 51.6f);

    v2f -= v1f;
    assert(v2f.x == 10.2f);
    assert(v2f.y == -51.6f);
}

void vector_mult_scalar()
{
    physm::Vector2<int> v1(13, 5);
    physm::Vector2<int> res = v1 * 0;
    assert(res.x == 0);
    assert(res.x == 0);

    res = v1 * 13;
    assert(res.x == 169);
    assert(res.y == 65);

    physm::Vector2<float> v1f(3.0f, 1.5f);
    physm::Vector2<float> res_f = v1f * 0.0f;
    assert(res_f.x == 0.0f);
    assert(res_f.y == 0.0f);

    res_f = v1f * -2.5;
    assert(res_f.x == -7.5f);
    assert(res_f.y == -3.75f);
}

void vector_div_scalar()
{
    physm::Vector2<int> v1(0, 0);
    physm::Vector2<int> res = v1 / 15;
    assert(res.x == 0);
    assert(res.y == 0);

    v1 = physm::Vector2<int>(125, 25);
    res = v1 / 25;
    assert(res.x == 5);
    assert(res.y == 1);

    physm::Vector2<float> v1f(0.0f, 0.0f);
    physm::Vector2<float> res_f = v1f / 1321.1321f;
    assert(res_f.x == 0.0f);
    assert(res_f.y == 0.0f);
}

void vector_neg()
{
    physm::Vector2<int> v1(-5, 13);
    physm::Vector2<int> res = -v1;
    assert(res.x == 5);
    assert(res.y == -13);

    v1 = physm::Vector2<int>(0, 0);
    res = -v1;
    assert(res.x == 0);
    assert(res.y == 0);

    physm::Vector2<float> v1f(-123.33f, 67.67f);
    physm::Vector2<float> res_f = -v1f;
    assert(res_f.x == 123.33f);
    assert(res_f.y == -67.67f);

    v1f = physm::Vector2<float>(0.0f, 0.0f);
    res_f = -v1f;
    assert(res_f.x == 0.0f);
    assert(res_f.y == 0.0f);
}

void vector_equal()
{
    physm::Vector2<int> v1(12, 3);
    physm::Vector2<int> v2(12, 3);
    assert(v1 == v2);
    assert(!(v1 == -v2));

    physm::Vector2<float> v1f(123.123f, 0.005f);
    physm::Vector2<float> v2f(123.123f, 0.005f);
    assert(v1f == v2f);
    assert(!(v1f == -v2f));

    v1f = physm::Vector2<float>(1.0f, 2.0f);
    v2f = physm::Vector2<float>(1.00001f, 2.0f);
    assert(!(v1f == v2f));
}

void vector_length()
{
    physm::Vector2<int> v1(3, 4);
    float res = v1.length();
    assert(res == 5.0f);

    physm::Vector2<float> v1f(4.0f, 3.0f);
    res = v1f.length();
    assert(res == 5.0f);
}

void vector_squared_length()
{
    physm::Vector2<int> v1(0, 15);
    float res = v1.length_squared();
    assert(res == 225.0f);

    v1 = physm::Vector2<int>(-15, 15);
    res = v1.length_squared();
    assert(res == 450.0f);

    physm::Vector2<float> v1f(3.0f, 4.0f);
    res = v1f.length_squared();
    assert(res == 25.0f);

    v1f = physm::Vector2<float>(4.5f, 0.1f);
    res = v1f.length_squared();
    assert(res == 20.26f);
}

void vector_normalize() 
{
    physm::Vector2<int> v1(3, 4);
    physm::Vector2<float> res = normalize(v1);
    assert(res.x == 0.6f);
    assert(res.y == 0.8f);

    physm::Vector2<float> v1f(3.0f, 4.0f);
    res = normalize(v1f);
    assert(res.x == 0.6f);
    assert(res.y == 0.8f);
}

void vector_dot()
{
    physm::Vector2<int> v1(3, 4);
    physm::Vector2<int> v2(12, -1);
    int res = dot(v1, v2);
    assert(res == 32);

    v1 = physm::Vector2<int>(0, 0);
    res = dot(v1, v2);
    assert(res == 0);

    physm::Vector2<float> v1f(3.0f, 4.0f);
    physm::Vector2<float> v2f(12.0f, -1.0f);
    float res_f = dot(v1f, v2f);
    assert(res_f == 32.0f);

    v1f = physm::Vector2<float>(0.0f, 0.0f);
    res_f = dot(v1f, v2f);
    assert(res_f == 0.0f);
}

void vector_cross()
{
    physm::Vector2<int> v1(3, 4);
    physm::Vector2<int> v2(12, -1);
    int res = cross(v1, v2);
    assert(res == -51);
    res = cross(v2, v1);
    assert(res == 51);  

    v1 = physm::Vector2<int>(0, 0);
    res = cross(v1, v2);
    assert(res == 0);

    physm::Vector2<float> v1f(3.0f, 4.0f);
    physm::Vector2<float> v2f(12.0f, -1.0f);
    float res_f = cross(v1f, v2f);
    assert(res_f == -51.0f);
    res_f = cross(v2f, v1f);
    assert(res_f == 51.0f);

    v1f = physm::Vector2<float>(0.0f, 0.0f);
    res_f = cross(v1f, v2f);
    assert(res_f == 0.0f);
}
