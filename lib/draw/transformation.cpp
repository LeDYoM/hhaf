#include "transformation.hpp"
#include <math.h>

#include <lib/core/debugsystem.hpp>
#include <lib/core/host.hpp>

namespace lib
{
	namespace draw
	{
		const Transform Transform::Identity = Transform{};

		constexpr const vector2df Transform::transformPoint(const f32 x, const f32 y) const noexcept
		{
			return vector2df{ m_matrix[0] * x + m_matrix[4] * y + m_matrix[12],
				m_matrix[1] * x + m_matrix[5] * y + m_matrix[13] };
		}

		constexpr const vector2df Transform::transformPoint(const vector2df& point) const noexcept
		{
			return transformPoint(point.x, point.y);
		}

		const Rectf32 Transform::transformRect(const Rectf32& rectangle) const noexcept
		{
			// Transform the 4 corners of the rectangle
			const vector2df points[4] =
			{
				transformPoint(rectangle.left, rectangle.top),
				transformPoint(rectangle.left, rectangle.top + rectangle.height),
				transformPoint(rectangle.left + rectangle.width, rectangle.top),
				transformPoint(rectangle.left + rectangle.width, rectangle.top + rectangle.height)
			};

			// Compute the bounding rectangle of the transformed points
			f32 left{ points[0].x };
			f32 top{ points[0].y };
			f32 right{ points[0].x };
			f32 bottom{ points[0].y };
			for (const auto& point : points)
			{
				if (point.x < left)   left = point.x;
				else if (point.x > right)  right = point.x;
				if (point.y < top)    top = point.y;
				else if (point.y > bottom) bottom = point.y;
			}

			return Rectf32{left, top, right - left, bottom - top};
		}

		Transform& Transform::combine(const Transform& transform) noexcept
		{
			const f32* a = &(m_matrix[0]);
			const f32* b = &(transform.m_matrix[0]);

			*this = Transform{ a[0] * b[0] + a[4] * b[1] + a[12] * b[3],
				a[0] * b[4] + a[4] * b[5] + a[12] * b[7],
				a[0] * b[12] + a[4] * b[13] + a[12] * b[15],
				a[1] * b[0] + a[5] * b[1] + a[13] * b[3],
				a[1] * b[4] + a[5] * b[5] + a[13] * b[7],
				a[1] * b[12] + a[5] * b[13] + a[13] * b[15],
				a[3] * b[0] + a[7] * b[1] + a[15] * b[3],
				a[3] * b[4] + a[7] * b[5] + a[15] * b[7],
				a[3] * b[12] + a[7] * b[13] + a[15] * b[15] };

			return *this;
		}

		Transform& Transform::translate(const f32 x, const f32 y) noexcept
		{
			return combine(Transform{ 1, 0, x,
				0, 1, y,
				0, 0, 1 });
		}

		Transform& Transform::translate(const vector2df& offset) noexcept
		{
			return translate(offset.x, offset.y);
		}

		static constexpr f32 radFactor = 3.141592654f / 180.f;

		Transform& Transform::rotate(const f32 angle) noexcept
		{
			const f32 rad = angle * radFactor;
			const f32 cos = std::cos(rad);
			const f32 sin = std::sin(rad);

			return combine(Transform{ cos, -sin, 0,
				sin, cos, 0,
				0, 0, 1 });
		}

		Transform& Transform::rotate(const f32 angle, const f32 centerX, const f32 centerY) noexcept
		{
			const f32 rad = angle * radFactor;
			const f32 cos = std::cos(rad);
			const f32 sin = std::sin(rad);

			return combine(Transform{ cos, -sin, centerX * (1 - cos) + centerY * sin,
				sin, cos, centerY * (1 - cos) - centerX * sin,
				0, 0, 1});
		}

		Transform& Transform::rotate(const f32 angle, const vector2df& center) noexcept
		{
			return rotate(angle, center.x, center.y);
		}

		Transform& Transform::scale(const f32 scaleX, const f32 scaleY) noexcept
		{
			Transform scaling{ scaleX, 0, 0,
				0, scaleY, 0,
				0, 0, 1 };

			return combine(scaling);
		}

		Transform& Transform::scale(const f32 scaleX, const f32 scaleY, const f32 centerX, const f32 centerY) noexcept
		{
			return combine(Transform{ scaleX, 0, centerX * (1 - scaleX),
				0, scaleY, centerY * (1 - scaleY),
				0, 0, 1 });
		}

		Transform& Transform::scale(const vector2df& factors) noexcept
		{
			return scale(factors.x, factors.y);
		}

		Transform& Transform::scale(const vector2df& factors, const vector2df& center) noexcept
		{
			return scale(factors.x, factors.y, center.x, center.y);
		}
	}
}
