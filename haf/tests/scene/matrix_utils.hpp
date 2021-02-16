#ifndef HAF_SCENE_MATRIX_UTILS_TEST_INCLUDE_HPP
#define HAF_SCENE_MATRIX_UTILS_TEST_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/scene/include/matrix4x4.hpp>
#include <limits>

namespace haf::scene::testing
{
inline bool isAlmostEqual(mtps::f32 const lhs, mtps::f32 const rhs)
{
    return std::abs(lhs - rhs) < std::numeric_limits<mtps::f32>::epsilon();
}

inline bool isAlmostEqual(Matrix4x4 const& lhs, Matrix4x4 const& rhs)
{
    for (auto index{0U}; index < 16U; ++index)
    {
        if (!isAlmostEqual(lhs.getMatrix()[index], rhs.getMatrix()[index]))
        {
            return false;
        }
    }
    return true;
}

}  // namespace haf::scene::testing

#endif
