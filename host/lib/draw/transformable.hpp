#ifndef LIB_TRANSFORMABLE_INCLUDE_HPP
#define LIB_TRANSFORMABLE_INCLUDE_HPP

#include <SFML/Graphics/Transform.hpp>
#include <lib/include/vector2d.hpp>

namespace lib
{
	namespace draw
	{
		class Transformable
		{
		public:

			Transformable();
			virtual ~Transformable();
			void setPosition(float x, float y);
			void setPosition(const vector2df& position);
			void setRotation(float angle);
			void setScale(float factorX, float factorY);
			void setScale(const vector2df& factors);
			void setOrigin(float x, float y);
			void setOrigin(const vector2df& origin);
			const vector2df& getPosition() const;
			float getRotation() const;
			const vector2df& getScale() const;
			const vector2df& getOrigin() const;
			void move(float offsetX, float offsetY);
			void move(const vector2df& offset);
			void rotate(float angle);
			void scale(float factorX, float factorY);
			void scale(const vector2df& factor);
			const sf::Transform& getTransform() const;
			const sf::Transform& getInverseTransform() const;

		private:

			vector2df          m_origin;
			vector2df          m_position;
			float             m_rotation;
			vector2df          m_scale;
			mutable sf::Transform m_transform;
			mutable bool      m_transformNeedUpdate;
			mutable sf::Transform m_inverseTransform;
			mutable bool      m_inverseTransformNeedUpdate;
		};
	}
}

#endif
