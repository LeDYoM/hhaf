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
			void setPosition(const f32 x, const f32 y);
			void setPosition(const vector2df& position);
			void setRotation(const f32 angle);
			void setScale(const f32 factorX, const f32 factorY);
			void setScale(const vector2df& factors);
			void setOrigin(const f32 x, const f32 y);
			void setOrigin(const vector2df& origin);
			const vector2df& getPosition() const;
			f32 getRotation() const;
			const vector2df& getScale() const;
			const vector2df& getOrigin() const;
			void move(const f32 offsetX, const f32 offsetY);
			void move(const vector2df& offset);
			void rotate(const f32 angle);
			void scale(const f32 factorX, const f32 factorY);
			void scale(const vector2df& factor);
			const sf::Transform& getTransform() const;
			const sf::Transform& getInverseTransform() const;

		private:

			vector2df m_origin;
			vector2df m_position;
			f32 m_rotation;
			vector2df m_scale;
			mutable sf::Transform m_transform;
			mutable bool m_transformNeedUpdate;
			mutable sf::Transform m_inverseTransform;
			mutable bool m_inverseTransformNeedUpdate;
		};
	}
}

#endif
