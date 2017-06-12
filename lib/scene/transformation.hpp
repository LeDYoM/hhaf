#ifndef LIB_TRANSFORMATION_INCLUDE_HPP__
#define LIB_TRANSFORMATION_INCLUDE_HPP__

#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>

namespace lib
{
	namespace scene
	{
		class Transform final
		{
		public:
			constexpr Transform() noexcept
				: m_matrix{ 1.f, 0.f, 0.f, 0.f,
				0.f, 1.f, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f } {}

			constexpr Transform(const f32 a00, const f32 a01, const f32 a02,
				const f32 a10, const f32 a11, const f32 a12,
				const f32 a20, const f32 a21, const f32 a22) noexcept
				: m_matrix{ a00, a10, 0.f, a20,
				a01, a11, 0.f, a21,
				0.f, 0.f, 1.f, 0.f,
				a02, a12, 0.f, a22 } {}

			constexpr Transform(const Transform&) noexcept = default;
			Transform& operator=(const Transform&) noexcept = default;

			constexpr Transform(Transform&&) noexcept = default;
			Transform& operator=(Transform&&) noexcept = default;

			constexpr const f32* const getMatrix() const noexcept { return &m_matrix[0]; }
			static const Transform Identity;
			inline Transform& operator *=(const Transform& right) noexcept
			{
				return combine(right);
			}

			const Transform operator *(const Transform& right) const noexcept
			{
				Transform copy{ *this };
				copy.combine(right);
				return copy;
			}

			constexpr const vector2df operator *(const vector2df& right) const noexcept
			{
				return this->transformPoint(right);
			}

			constexpr const vector2df transformPoint(const f32 x, const f32 y) const noexcept;
			constexpr const vector2df transformPoint(const vector2df& point) const noexcept;
			const Rectf32 transformRect(const Rectf32& rectangle) const noexcept;
			Transform& combine(const Transform& transform) noexcept;
			Transform& translate(const f32 x, const f32 y) noexcept;
			Transform& translate(const vector2df& offset) noexcept;
			Transform& rotate(const f32 angle) noexcept;
			Transform& rotate(const f32 angle, const f32 centerX, const f32 centerY) noexcept;
			Transform& rotate(const f32 angle, const vector2df& center) noexcept;
			Transform& scale(const f32 scaleX, const f32 scaleY) noexcept;
			Transform& scale(const f32 scaleX, const f32 scaleY, const f32 centerX, const f32 centerY) noexcept;
			Transform& scale(const vector2df& factors) noexcept;
			Transform& scale(const vector2df& factors, const vector2df& center) noexcept;

		private:
			f32 m_matrix[16];
		};
	}
}

#endif
