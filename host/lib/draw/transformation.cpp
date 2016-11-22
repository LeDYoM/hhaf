#include "transformation.hpp"
#include <cmath>

namespace lib
{
	namespace draw
	{
		const Transform Transform::Identity;

		Transform::Transform() noexcept
			: m_matrix{ 1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f }
		{
		}

		Transform::Transform(const f32 a00, const f32 a01, const f32 a02,
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

		Transform Transform::getInverse() const
		{
			// Compute the determinant
			f32 det = m_matrix[0] * (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) -
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

		vector2df Transform::transformPoint(const f32 x, const f32 y) const
		{
			return vector2df(m_matrix[0] * x + m_matrix[4] * y + m_matrix[12],
				m_matrix[1] * x + m_matrix[5] * y + m_matrix[13]);
		}

		vector2df Transform::transformPoint(const vector2df& point) const
		{
			return transformPoint(point.x, point.y);
		}

		sf::FloatRect Transform::transformRect(const sf::FloatRect& rectangle) const
		{
			// Transform the 4 corners of the rectangle
			const vector2df points[] =
			{
				transformPoint(rectangle.left, rectangle.top),
				transformPoint(rectangle.left, rectangle.top + rectangle.height),
				transformPoint(rectangle.left + rectangle.width, rectangle.top),
				transformPoint(rectangle.left + rectangle.width, rectangle.top + rectangle.height)
			};

			// Compute the bounding rectangle of the transformed points
			float left = points[0].x;
			float top = points[0].y;
			float right = points[0].x;
			float bottom = points[0].y;
			for (int i = 1; i < 4; ++i)
			{
				if (points[i].x < left)   left = points[i].x;
				else if (points[i].x > right)  right = points[i].x;
				if (points[i].y < top)    top = points[i].y;
				else if (points[i].y > bottom) bottom = points[i].y;
			}

			return sf::FloatRect(left, top, right - left, bottom - top);
		}

		Transform& Transform::combine(const Transform& transform)
		{
			const float* a = getMatrix();
			const float* b = transform.getMatrix();

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

		Transform& Transform::translate(const f32 x, const f32 y)
		{
			Transform translation(1, 0, x,
				0, 1, y,
				0, 0, 1);

			return combine(translation);
		}

		Transform& Transform::translate(const vector2df& offset)
		{
			return translate(offset.x, offset.y);
		}

		Transform& Transform::rotate(const f32 angle)
		{
			float rad = angle * 3.141592654f / 180.f;
			float cos = std::cos(rad);
			float sin = std::sin(rad);

			Transform rotation(cos, -sin, 0,
				sin, cos, 0,
				0, 0, 1);

			return combine(rotation);
		}

		Transform& Transform::rotate(const f32 angle, const f32 centerX, const f32 centerY)
		{
			float rad = angle * 3.141592654f / 180.f;
			float cos = std::cos(rad);
			float sin = std::sin(rad);

			Transform rotation(cos, -sin, centerX * (1 - cos) + centerY * sin,
				sin, cos, centerY * (1 - cos) - centerX * sin,
				0, 0, 1);

			return combine(rotation);
		}

		Transform& Transform::rotate(const f32 angle, const vector2df& center)
		{
			return rotate(angle, center.x, center.y);
		}

		Transform& Transform::scale(const f32 scaleX, const f32 scaleY)
		{
			Transform scaling(scaleX, 0, 0,
				0, scaleY, 0,
				0, 0, 1);

			return combine(scaling);
		}

		Transform& Transform::scale(const f32 scaleX, const f32 scaleY, const f32 centerX, const f32 centerY)
		{
			Transform scaling(scaleX, 0, centerX * (1 - scaleX),
				0, scaleY, centerY * (1 - scaleY),
				0, 0, 1);

			return combine(scaling);
		}

		Transform& Transform::scale(const vector2df& factors)
		{
			return scale(factors.x, factors.y);
		}

		Transform& Transform::scale(const vector2df& factors, const vector2df& center)
		{
			return scale(factors.x, factors.y, center.x, center.y);
		}

		Transform::operator sf::Transform() const noexcept
		{
			return sf::Transform(m_matrix[0], m_matrix[4], m_matrix[12],
				m_matrix[1], m_matrix[5], m_matrix[13],
				m_matrix[3], m_matrix[7], m_matrix[15]);
		}

		Transform operator *(const Transform& left, const Transform& right)
		{
			return Transform(left).combine(right);
		}

		Transform& operator *=(Transform& left, const Transform& right)
		{
			return left.combine(right);
		}

		vector2df operator *(const Transform& left, const vector2df& right)
		{
			return left.transformPoint(right);
		}
	}
}
