#include "catch.hpp"

#include <htypes/include/types.hpp>
#include <haf/include/scene/matrix4x4.hpp>
#include "matrix_utils.hpp"
#include <limits>

using namespace haf;
using namespace haf::scene;
using namespace haf::scene::testing;

TEST_CASE("haf::scene::Matrix4x4", "[haf][scene][Matrix4x4][Transformable]")
{
    Matrix4x4 matrix;
    CHECK(isAlmostEqual(matrix, Matrix4x4::Identity));

    Matrix4x4 matrix2(100.0F, 200.0F, 300.0F, 400.0F, 500.0F, 600.0F, 700.0F,
                      800.0F, 900.0F);

    CHECK(isAlmostEqual(matrix2.getMatrix()[0U], 100.0F));
    CHECK(isAlmostEqual(matrix2.getMatrix()[4U], 200.0F));
    CHECK(isAlmostEqual(matrix2.getMatrix()[8U], Matrix4x4::Zero));
    CHECK(isAlmostEqual(matrix2.getMatrix()[12U], 300.0F));
    CHECK(isAlmostEqual(matrix2.getMatrix()[1U], 400.0F));
    CHECK(isAlmostEqual(matrix2.getMatrix()[5U], 500.0F));
    CHECK(isAlmostEqual(matrix2.getMatrix()[9U], Matrix4x4::Zero));
    CHECK(isAlmostEqual(matrix2.getMatrix()[13U], 600.0F));
    CHECK(isAlmostEqual(matrix2.getMatrix()[2U], Matrix4x4::Zero));
    CHECK(isAlmostEqual(matrix2.getMatrix()[6U], Matrix4x4::Zero));
    CHECK(isAlmostEqual(matrix2.getMatrix()[10U], Matrix4x4::One));
    CHECK(isAlmostEqual(matrix2.getMatrix()[14U], Matrix4x4::Zero));
    CHECK(isAlmostEqual(matrix2.getMatrix()[3U], 700.0F));
    CHECK(isAlmostEqual(matrix2.getMatrix()[7U], 800.0F));
    CHECK(isAlmostEqual(matrix2.getMatrix()[11U], Matrix4x4::Zero));
    CHECK(isAlmostEqual(matrix2.getMatrix()[15U], 900.0F));
}

TEST_CASE("haf::scene::Matrix4x4 math",
          "[haf][scene][Matrix4x4][Transformable]")
{
    Matrix4x4 matrix1;
    Matrix4x4 matrix2(100.0F, 200.0F, 300.0F, 400.0F, 500.0F, 600.0F, 700.0F,
                      800.0F, 900.0F);

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

TEST_CASE("haf::scene::Matrix4x4 Benchmark",
          "[haf][scene][Matrix4x4][Transformable][benchmark]")
{
    Matrix4x4 const matrix1(100.0F, 200.0F, 300.0F, 400.0F, 500.0F, 600.0F,
                            700.0F, 800.0F, 900.0F);

    Matrix4x4 const matrix2(12345.123F, 245349786.1F, 3456710823.1234F,
                            4.1298654345F, 5765.51298F, 63703610952.22F,
                            0.0000124F, 0.9999999990F, 9.0F);

    BENCHMARK("Matrix4x4 copy constructor")
    {
        Matrix4x4 copy{matrix1};
        Matrix4x4 copy2{matrix2};
        (void)(copy);
        (void)(copy2);
    };

    Matrix4x4 copy;

    BENCHMARK("Matrix4x4 copy asignment") { copy = matrix2; };

    BENCHMARK("Matrix4x4 equal multiply") { copy *= matrix2; };

    BENCHMARK("Matrix4x4 multiply")
    {
        Matrix4x4 copy = matrix1 * matrix2;
        (void)(copy);
    };
}