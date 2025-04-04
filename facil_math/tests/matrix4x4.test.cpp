#include "catch_include.hpp"

#include <facil_math/include/matrix4x4.hpp>
#include <limits>

using namespace fmath;

TEST_CASE("haf::math::Matrix4x4", "[haf][scene][Matrix4x4][Transformable]")
{
    Matrix4x4 matrix;
    CHECK(matrix == Matrix4x4::Identity);

    Matrix4x4 matrix2(100.0F, 200.0F, 300.0F, 400.0F, 500.0F, 600.0F, 700.0F,
                      800.0F, 900.0F, 1000.0F, 1100.0F, 1200.0F, 1300.0F,
                      1400.0F, 1500.0F, 1600.0F);

    Matrix4x4 matrix3(100.0F, 200.0F, 300.0F, 400.0F, 500.0F, 600.0F, 700.0F,
                      800.0F, 900.0F, 1000.0F, 1100.0F, 1200.0F, 1300.0F,
                      1400.0F, 1500.0F, 1600.0F);

    CHECK(isAlmostEqual(matrix2, matrix3));
}

TEST_CASE("haf::math::Matrix4x4 math", "[haf][scene][Matrix4x4]")
{
    Matrix4x4 matrix1;
    Matrix4x4 matrix2(100.0F, 200.0F, 300.0F, 400.0F, 500.0F, 600.0F, 700.0F,
                      800.0F, 900.0F, 1000.0F, 1100.0F, 1200.0F, 1300.0F,
                      1400.0F, 1500.0F, 1600.0F);

    {
        Matrix4x4 matrix3 = matrix1 * matrix2;
        CHECK(isAlmostEqual(matrix2, matrix3));
    }

    {
        Matrix4x4 matrix3 = matrix2 * matrix1;
        CHECK(isAlmostEqual(matrix2, matrix3));
    }

    {
        Matrix4x4 matrix3 = matrix2 * matrix1 * matrix2;
        CHECK_FALSE(isAlmostEqual(matrix2, matrix3));
    }

    {
        Matrix4x4 matrix3 = matrix1 * matrix1 * matrix1;
        CHECK_FALSE(isAlmostEqual(matrix2, matrix3));
    }
}

TEST_CASE("haf::math::Matrix4x4::setColumn", "[haf][scene][Matrix4x4]")
{
    {
        Matrix4x4 matrix1;
        CHECK(isAlmostEqual(matrix1, Matrix4x4::Identity));

        matrix1.setColumn<0U>({5.4F, 8.5F, 9.6F, 10.7F});
        CHECK(isAlmostEqual(
            matrix1,
            Matrix4x4{5.4F, 8.5F, 9.6F, 10.7F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F,
                      0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F}));
    }

    {
        Matrix4x4 matrix1;
        CHECK(isAlmostEqual(matrix1, Matrix4x4::Identity));

        matrix1.setColumn<1U>({5.4F, 8.5F, 9.6F, 10.7F});
        CHECK(isAlmostEqual(
            matrix1,
            Matrix4x4{1.0F, 0.0F, 0.0F, 0.0F, 5.4F, 8.5F, 9.6F, 10.7F, 0.0F,
                      0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F}));
    }

    {
        Matrix4x4 matrix1;
        CHECK(isAlmostEqual(matrix1, Matrix4x4::Identity));

        matrix1.setColumn<2U>({5.4F, 8.5F, 9.6F, 10.7F});
        CHECK(isAlmostEqual(
            matrix1,
            Matrix4x4{1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 5.4F,
                      8.5F, 9.6F, 10.7F, 0.0F, 0.0F, 0.0F, 1.0F}));
    }

    {
        Matrix4x4 matrix1;
        CHECK(isAlmostEqual(matrix1, Matrix4x4::Identity));

        matrix1.setColumn<3U>({5.4F, 8.5F, 9.6F, 10.7F});
        CHECK(isAlmostEqual(
            matrix1,
            Matrix4x4{1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F,
                      0.0F, 1.0F, 0.0F, 5.4F, 8.5F, 9.6F, 10.7F}));
    }

    {
        Matrix4x4 matrix1;
        CHECK(isAlmostEqual(matrix1, Matrix4x4::Identity));

        matrix1.setColumn<0U>({5.4F, 8.5F, 9.6F, 10.7F});
        matrix1.setColumn<1U>({5.4F, 8.5F, 9.6F, 10.7F});
        matrix1.setColumn<2U>({5.4F, 8.5F, 9.6F, 10.7F});
        matrix1.setColumn<3U>({5.4F, 8.5F, 9.6F, 10.7F});

        CHECK(isAlmostEqual(
            matrix1,
            Matrix4x4{5.4F, 8.5F, 9.6F, 10.7F, 5.4F, 8.5F, 9.6F, 10.7F, 5.4F,
                      8.5F, 9.6F, 10.7F, 5.4F, 8.5F, 9.6F, 10.7F}));
    }
}

TEST_CASE("haf::math::Matrix4x4::operator*", "[haf][scene][Matrix4x4]")
{}