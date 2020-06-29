#include "transform.hpp"
#include "geometry_math.hpp"
#include <math.h>

namespace haf::scene
{
const Transform Transform::Identity = Transform{};

Transform::VectorScalar Transform::transformPoint(Scalar const x,
                                                  Scalar const y) const noexcept
{
    return {
        (matrix_data_[0U] * x) + (matrix_data_[4U] * y) + matrix_data_[12U],
        (matrix_data_[1U] * x) + (matrix_data_[5U] * y) + matrix_data_[13U]};
}

Transform::VectorScalar Transform::transformPoint(
    VectorScalar const& point) const noexcept
{
    return transformPoint(point.x, point.y);
}

Transform::RectScalar Transform::transformRect(
    RectScalar const& rectangle) const noexcept
{
    // Transform the 4 corners of the rectangle
    VectorScalar const points[4U] = {
        transformPoint(rectangle.left, rectangle.top),
        transformPoint(rectangle.left, rectangle.top + rectangle.height),
        transformPoint(rectangle.left + rectangle.width, rectangle.top),
        transformPoint(rectangle.left + rectangle.width,
                       rectangle.top + rectangle.height)};

    // Compute the bounding rectangle of the transformed points
    Scalar left{points[0U].x}, top{points[0U].y}, right{points[0U].x},
        bottom{points[0U].y};

    for (auto const& point : points)
    {
        if (point.x < left)
        {
            left = point.x;
        }
        else if (point.x > right)
        {
            right = point.x;
        }

        if (point.y < top)
        {
            top = point.y;
        }
        else if (point.y > bottom)
        {
            bottom = point.y;
        }
    }

    return {left, top, right - left, bottom - top};
}

Transform& Transform::combine(Transform const& transform) noexcept
{
    const Scalar* const a{&(matrix_data_[0U])};
    const Scalar* const b{&(transform.matrix_data_[0U])};

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

Transform& Transform::translate(Scalar const x, Scalar const y) noexcept
{
    return combine({One, Zero, x, Zero, One, y, Zero, Zero, One});
}

Transform& Transform::translate(VectorScalar const& offset) noexcept
{
    return translate(offset.x, offset.y);
}

Transform& Transform::rotate(Scalar const angle) noexcept
{
    auto const rad{angle * ToRadians<Scalar>};
    auto const cos{static_cast<Scalar>(std::cos(rad))};
    auto const sin{static_cast<Scalar>(std::sin(rad))};

    return combine({cos, -sin, Zero, sin, cos, Zero, Zero, Zero, One});
}

Transform& Transform::rotate(Scalar const angle,
                             Scalar const centerX,
                             Scalar const centerY) noexcept
{
    auto const rad{static_cast<Scalar>(angle * ToRadians<Scalar>)};
    auto const cos{static_cast<Scalar>(std::cos(rad))};
    auto const sin{static_cast<Scalar>(std::sin(rad))};

    return combine({cos, -sin, centerX * (One - cos) + centerY * sin, sin, cos,
                    centerY * (One - cos) - centerX * sin, Zero, Zero, One});
}

Transform& Transform::rotate(Scalar const angle,
                             VectorScalar const& center) noexcept
{
    return rotate(angle, center.x, center.y);
}

Transform& Transform::scale(Scalar const scaleX, Scalar const scaleY) noexcept
{
    return combine({scaleX, Zero, Zero, Zero, scaleY, Zero, Zero, Zero, One});
}

Transform& Transform::scale(Scalar const scaleX,
                            Scalar const scaleY,
                            Scalar const centerX,
                            Scalar const centerY) noexcept
{
    return combine({scaleX, Zero, centerX * (One - scaleX), Zero, scaleY,
                    centerY * (One - scaleY), Zero, Zero, One});
}

Transform& Transform::scale(VectorScalar const& factors) noexcept
{
    return scale(factors.x, factors.y);
}

Transform& Transform::scale(VectorScalar const& factors,
                            VectorScalar const& center) noexcept
{
    return scale(factors.x, factors.y, center.x, center.y);
}
}  // namespace haf::scene
