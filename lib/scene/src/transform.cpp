#include "transform.hpp"
#include "geometry_math.hpp"
#include <math.h>

namespace haf::scene
{
const Transform Transform::Identity = Transform{};

Transform::VectorScalar Transform::transformPoint(const Scalar x, const Scalar y) const noexcept
{
    return {(m_matrix[0U] * x) + (m_matrix[4U] * y) + m_matrix[12U],
            (m_matrix[1U] * x) + (m_matrix[5U] * y) + m_matrix[13U]};
}

Transform::VectorScalar Transform::transformPoint(const VectorScalar &point) const noexcept
{
    return transformPoint(point.x, point.y);
}

Transform::RectScalar Transform::transformRect(const RectScalar &rectangle) const noexcept
{
    // Transform the 4 corners of the rectangle
    const VectorScalar points[4U] =
        {
            transformPoint(rectangle.left, rectangle.top),
            transformPoint(rectangle.left, rectangle.top + rectangle.height),
            transformPoint(rectangle.left + rectangle.width, rectangle.top),
            transformPoint(rectangle.left + rectangle.width, rectangle.top + rectangle.height)};

    // Compute the bounding rectangle of the transformed points
    Scalar left{points[0U].x},
        top{points[0U].y},
        right{points[0U].x},
        bottom{points[0U].y};

    for (const auto &point : points)
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

Transform &Transform::combine(const Transform &transform) noexcept
{
    const Scalar *const a{&(m_matrix[0U])};
    const Scalar *const b{&(transform.m_matrix[0U])};

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

Transform &Transform::translate(const Scalar x, const Scalar y) noexcept
{
    return combine({One, Zero, x,
                    Zero, One, y,
                    Zero, Zero, One});
}

Transform &Transform::translate(const VectorScalar &offset) noexcept
{
    return translate(offset.x, offset.y);
}

Transform &Transform::rotate(const Scalar angle) noexcept
{
    const Scalar rad{angle * ToRadians<Scalar>};
    const Scalar cos{static_cast<Scalar>(std::cos(rad))};
    const Scalar sin{static_cast<Scalar>(std::sin(rad))};

    return combine({cos, -sin, Zero,
                    sin, cos, Zero,
                    Zero, Zero, One});
}

Transform &Transform::rotate(
    const Scalar angle, const Scalar centerX, const Scalar centerY) noexcept
{
    const Scalar rad{static_cast<Scalar>(angle * ToRadians<Scalar>)};
    const Scalar cos{static_cast<Scalar>(std::cos(rad))};
    const Scalar sin{static_cast<Scalar>(std::sin(rad))};

    return combine({cos, -sin, centerX * (One - cos) + centerY * sin,
                    sin, cos, centerY * (One - cos) - centerX * sin,
                    Zero, Zero, One});
}

Transform &Transform::rotate(const Scalar angle, const VectorScalar &center) noexcept
{
    return rotate(angle, center.x, center.y);
}

Transform &Transform::scale(const Scalar scaleX, const Scalar scaleY) noexcept
{
    return combine({scaleX, Zero, Zero,
                    Zero, scaleY, Zero,
                    Zero, Zero, One});
}

Transform &Transform::scale(
    const Scalar scaleX, const Scalar scaleY,
    const Scalar centerX, const Scalar centerY) noexcept
{
    return combine({scaleX, Zero, centerX * (One - scaleX),
                    Zero, scaleY, centerY * (One - scaleY),
                    Zero, Zero, One});
}

Transform &Transform::scale(const VectorScalar &factors) noexcept
{
    return scale(factors.x, factors.y);
}

Transform &Transform::scale(const VectorScalar &factors, const VectorScalar &center) noexcept
{
    return scale(factors.x, factors.y, center.x, center.y);
}
} // namespace haf::scene
