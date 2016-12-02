#ifndef LIB_TRANSFORMATION_INCLUDE_HPP__
#define LIB_TRANSFORMATION_INCLUDE_HPP__

#include <lib/include/vector2d.hpp>
#include <lib/include/rect.hpp>
#include <SFML/Graphics.hpp>

#include <array>

namespace lib
{
	namespace draw
	{
		class Transform
		{
		public:
			constexpr Transform() noexcept;
			constexpr Transform(const f32 a00, const f32 a01, const f32 a02,
				const f32 a10, const f32 a11, const f32 a12,
				const f32 a20, const f32 a21, const f32 a22) noexcept;

			constexpr Transform(const Transform&) noexcept = default;
			Transform& operator=(const Transform&) noexcept = default;

			constexpr Transform(Transform&&) noexcept = default;
			Transform& operator=(Transform&&) noexcept = default;

			constexpr inline const f32* const getMatrix() const noexcept { return &m_matrix[0]; }
			Transform getInverse() const noexcept;
			constexpr vector2df transformPoint(const f32 x, const f32 y) const noexcept;
			constexpr vector2df transformPoint(const vector2df& point) const noexcept;
			Rectf32 transformRect(const Rectf32& rectangle) const noexcept;
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
			operator const sf::Transform() const noexcept;
			static const Transform Identity;
			Transform& operator *=(const Transform& right);

		private:
			std::array<f32, 16> m_matrix;
		};

		Transform operator *(const Transform& left, const Transform& right);
		vector2df operator *(const Transform& left, const vector2df& right);
	}
}

#endif
