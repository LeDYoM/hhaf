#ifndef LIB_TRANSFORMATION_INCLUDE_HPP__
#define LIB_TRANSFORMATION_INCLUDE_HPP__

#include <lib/include/vector2d.hpp>
#include <SFML/Graphics.hpp>

namespace lib
{
	namespace draw
	{
		class Transform
		{
		public:
			Transform();
			Transform(const f32 a00, const f32 a01, const f32 a02,
				const f32 a10, const f32 a11, const f32 a12,
				const f32 a20, const f32 a21, const f32 a22);

			const f32* getMatrix() const;
			Transform getInverse() const;
			vector2df transformPoint(const f32 x, const f32 y) const;
			vector2df transformPoint(const vector2df& point) const;
			sf::FloatRect transformRect(const sf::FloatRect& rectangle) const;
			Transform& combine(const Transform& transform);
			Transform& translate(const f32 x, const f32 y);
			Transform& translate(const vector2df& offset);
			Transform& rotate(const f32 angle);
			Transform& rotate(const f32 angle, const f32 centerX, const f32 centerY);
			Transform& rotate(const f32 angle, const vector2df& center);
			Transform& scale(const f32 scaleX, const f32 scaleY);
			Transform& scale(float scaleX, float scaleY, float centerX, float centerY);
			Transform& scale(const vector2df& factors);
			Transform& scale(const vector2df& factors, const vector2df& center);
			operator sf::Transform() const noexcept;
			static const Transform Identity;
		private:
			float m_matrix[16];
		};

		Transform operator *(const Transform& left, const Transform& right);
		Transform& operator *=(Transform& left, const Transform& right);
		vector2df operator *(const Transform& left, const vector2df& right);
	}
}

#endif
