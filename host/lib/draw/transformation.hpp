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
			Transform(float a00, float a01, float a02,
				float a10, float a11, float a12,
				float a20, float a21, float a22);

			const float* getMatrix() const;
			Transform getInverse() const;
			vector2df transformPoint(float x, float y) const;
			vector2df transformPoint(const vector2df& point) const;
			sf::FloatRect transformRect(const sf::FloatRect& rectangle) const;
			Transform& combine(const Transform& transform);
			Transform& translate(float x, float y);
			Transform& translate(const vector2df& offset);
			Transform& rotate(float angle);
			Transform& rotate(float angle, float centerX, float centerY);
			Transform& rotate(float angle, const vector2df& center);
			Transform& scale(float scaleX, float scaleY);
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
