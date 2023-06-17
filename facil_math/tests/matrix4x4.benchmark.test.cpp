#include "catch_include.hpp"

#include <htypes/include/types.hpp>
#include <facil_math/include/matrix4x4.hpp>

using namespace fmath;

TEST_CASE("facil_math::Matrix4x4 Benchmark",
          "[facil_math][Matrix4x4][benchmark]")
{
    Matrix4x4 const matrix1(100.0F, 200.0F, 300.0F, 400.0F, 500.0F, 600.0F,
                            700.0F, 800.0F, 900.0F, 1000.0F, 1100.0F, 1200.0F,
                            1300.0F, 1400.0F, 1500.0F, 1600.0F);

    Matrix4x4 const matrix2(100.0F, 200.0F, 300.0F, 400.0F, 500.0F, 600.0F,
                            700.0F, 800.0F, 900.0F, 1000.0F, 1100.0F, 1200.0F,
                            1300.0F, 1400.0F, 1500.0F, 1600.0F);

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