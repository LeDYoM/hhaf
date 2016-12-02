#ifndef LIB_TRANSFORMABLE_INCLUDE_HPP
#define LIB_TRANSFORMABLE_INCLUDE_HPP

#include "transformation.hpp"
#include <lib/include/vector2d.hpp>

namespace lib
{
	namespace draw
	{
		class Transformable
		{
		public:
			Transformable() noexcept;
			virtual ~Transformable();
			void setPosition(const vector2df& position);
			void setPositionX(const f32 x);
			void setPositionY(const f32 y);
			void setRotation(const f32 angle);
			void setScale(const vector2df& factors);
			void setOrigin(const vector2df& origin);
			const vector2df& getPosition() const;
			f32 getRotation() const;
			const vector2df& getScale() const;
			const vector2df& getOrigin() const;
			void move(const vector2df& offset);
			void rotate(const f32 angle);
			void scale(const vector2df& factor);
			const Transform& getTransform() const noexcept;
			void updateTransform();

		private:

			vector2df m_origin;
			vector2df m_position;
			f32 m_rotation;
			vector2df m_scale;
			Transform m_transform;
		};
	}
}

#endif
