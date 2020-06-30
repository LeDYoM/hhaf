#include "transform.hpp"
#include "geometry_math.hpp"
#include <math.h>

namespace haf::scene
{
const Transform Transform::Identity = Transform{};

Transform& Transform::operator*=(Transform const& transform) noexcept
{
    mtps::rptr<Scalar const> const a{matrix_data_};
    mtps::rptr<Scalar const> const b{transform.matrix_data_};

    *this = {(a[0U] * b[0U]) + (a[4U] * b[1U]) + (a[12U] * b[3U]),
             (a[0U] * b[4U]) + (a[4U] * b[5U]) + (a[12U] * b[7U]),
             (a[0U] * b[12U]) + (a[4U] * b[13U]) + (a[12U] * b[15U]),
             (a[1U] * b[0U]) + (a[5U] * b[1U]) + (a[13U] * b[3U]),
             (a[1U] * b[4U]) + (a[5U] * b[5U]) + (a[13U] * b[7U]),
             (a[1U] * b[12U]) + (a[5U] * b[13U]) + (a[13U] * b[15U]),
             (a[3U] * b[0U]) + (a[7U] * b[1U]) + (a[15U] * b[3U]),
             (a[3U] * b[4U]) + (a[7U] * b[5U]) + (a[15U] * b[7U]),
             (a[3U] * b[12U]) + (a[7U] * b[13U]) + (a[15U] * b[15U])};

    return *this;
}

}  // namespace haf::scene
