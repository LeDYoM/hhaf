#include "transformation.hpp"
#include <cmath>
#include <math.h>

namespace lib
{
	namespace draw
	{
		const Transform Transform::Identity = Transform{};

		constexpr Transform::Transform() noexcept
			: m_matrix{ 1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f } {}

		constexpr Transform::Transform(const f32 a00, const f32 a01, const f32 a02,
			const f32 a10, const f32 a11, const f32 a12,
			const f32 a20, const f32 a21, const f32 a22) noexcept
			: m_matrix{ a00, a10, 0.f, a20,
			a01, a11, 0.f, a21,
			0.f, 0.f, 1.f, 0.f,
			a02, a12, 0.f, a22 } 
		{
//			m_matrix[0] = a00; m_matrix[4] = a01; m_matrix[8] = 0.f; m_matrix[12] = a02;
//			m_matrix[1] = a10; m_matrix[5] = a11; m_matrix[9] = 0.f; m_matrix[13] = a12;
//			m_matrix[2] = 0.f; m_matrix[6] = 0.f; m_matrix[10] = 1.f; m_matrix[14] = 0.f;
//			m_matrix[3] = a20; m_matrix[7] = a21; m_matrix[11] = 0.f; m_matrix[15] = a22;
		}

		Transform Transform::getInverse() const noexcept
		{
			// Compute the determinant
			const f32 det = m_matrix[0] * (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) -
				m_matrix[1] * (m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) +
				m_matrix[3] * (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]);

			// Compute the inverse if the determinant is not zero
			// (don't use an epsilon because the determinant may *really* be tiny)
			if (det != 0.f)
			{
				return Transform((m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) / det,
					-(m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) / det,
					(m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]) / det,
					-(m_matrix[15] * m_matrix[1] - m_matrix[3] * m_matrix[13]) / det,
					(m_matrix[15] * m_matrix[0] - m_matrix[3] * m_matrix[12]) / det,
					-(m_matrix[13] * m_matrix[0] - m_matrix[1] * m_matrix[12]) / det,
					(m_matrix[7] * m_matrix[1] - m_matrix[3] * m_matrix[5]) / det,
					-(m_matrix[7] * m_matrix[0] - m_matrix[3] * m_matrix[4]) / det,
					(m_matrix[5] * m_matrix[0] - m_matrix[1] * m_matrix[4]) / det);
			}
			else
			{
				return Identity;
			}
		}

		constexpr vector2df Transform::transformPoint(const f32 x, const f32 y) const noexcept
		{
			return vector2df(m_matrix[0] * x + m_matrix[4] * y + m_matrix[12],
				m_matrix[1] * x + m_matrix[5] * y + m_matrix[13]);
		}

		constexpr vector2df Transform::transformPoint(const vector2df& point) const noexcept
		{
			return transformPoint(point.x, point.y);
		}

		Rectf32 Transform::transformRect(const Rectf32& rectangle) const noexcept
		{
			// Transform the 4 corners of the rectangle
			const std::array<vector2df,4> points =
			{
				transformPoint(rectangle.left, rectangle.top),
				transformPoint(rectangle.left, rectangle.top + rectangle.height),
				transformPoint(rectangle.left + rectangle.width, rectangle.top),
				transformPoint(rectangle.left + rectangle.width, rectangle.top + rectangle.height)
			};

			// Compute the bounding rectangle of the transformed points
			f32 left = points[0].x;
			f32 top = points[0].y;
			f32 right = points[0].x;
			f32 bottom = points[0].y;
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
			const std::array<f32,16> &a = m_matrix;
			const std::array<f32, 16> &b = transform.m_matrix;

			*this = Transform(a[0] * b[0] + a[4] * b[1] + a[12] * b[3],
				a[0] * b[4] + a[4] * b[5] + a[12] * b[7],
				a[0] * b[12] + a[4] * b[13] + a[12] * b[15],
				a[1] * b[0] + a[5] * b[1] + a[13] * b[3],
				a[1] * b[4] + a[5] * b[5] + a[13] * b[7],
				a[1] * b[12] + a[5] * b[13] + a[13] * b[15],
				a[3] * b[0] + a[7] * b[1] + a[15] * b[3],
				a[3] * b[4] + a[7] * b[5] + a[15] * b[7],
				a[3] * b[12] + a[7] * b[13] + a[15] * b[15]);

			return *this;
		}

		Transform& Transform::translate(const f32 x, const f32 y) noexcept
		{
			Transform translation(1, 0, x,
				0, 1, y,
				0, 0, 1);

			return combine(translation);
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

			Transform rotation(cos, -sin, 0,
				sin, cos, 0,
				0, 0, 1);

			return combine(rotation);
		}

		Transform& Transform::rotate(const f32 angle, const f32 centerX, const f32 centerY) noexcept
		{
			const f32 rad = angle * radFactor;
			const f32 cos = std::cos(rad);
			const f32 sin = std::sin(rad);

			Transform rotation(cos, -sin, centerX * (1 - cos) + centerY * sin,
				sin, cos, centerY * (1 - cos) - centerX * sin,
				0, 0, 1);

			return combine(rotation);
		}

		Transform& Transform::rotate(const f32 angle, const vector2df& center) noexcept
		{
			return rotate(angle, center.x, center.y);
		}

		Transform& Transform::scale(const f32 scaleX, const f32 scaleY) noexcept
		{
			Transform scaling(scaleX, 0, 0,
				0, scaleY, 0,
				0, 0, 1);

			return combine(scaling);
		}

		Transform& Transform::scale(const f32 scaleX, const f32 scaleY, const f32 centerX, const f32 centerY) noexcept
		{
			Transform scaling(scaleX, 0, centerX * (1 - scaleX),
				0, scaleY, centerY * (1 - scaleY),
				0, 0, 1);

			return combine(scaling);
		}

		Transform& Transform::scale(const vector2df& factors) noexcept
		{
			return scale(factors.x, factors.y);
		}

		Transform& Transform::scale(const vector2df& factors, const vector2df& center) noexcept
		{
			return scale(factors.x, factors.y, center.x, center.y);
		}

		Transform::operator sf::Transform() const noexcept
		{
			return sf::Transform(m_matrix[0], m_matrix[4], m_matrix[12],
				m_matrix[1], m_matrix[5], m_matrix[13],
				m_matrix[3], m_matrix[7], m_matrix[15]);
		}

		Transform & Transform::operator*=(const Transform & right)
		{
			return combine(right);
		}

		Transform operator *(const Transform& left, const Transform& right)
		{
			return Transform(left).combine(right);
		}

		vector2df operator *(const Transform& left, const vector2df& right)
		{
			return left.transformPoint(right);
		}
	}
}
