#ifndef LIB_TRANSFORMABLE_INCLUDE_HPP
#define LIB_TRANSFORMABLE_INCLUDE_HPP

#include "transformation.hpp"
#include <lib/include/vector2d.hpp>
#include <lib/include/properties.hpp>

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
			void setScale(const vector2df& factors);
			const vector2df& getPosition() const;
			const vector2df& getScale() const;
			const Transform& getTransform() const noexcept;
			void updateTransform();

			Property<vector2df> origin;
			Property<f32> rotation;

		private:

			vector2df m_position;
			vector2df m_scale;
			Transform m_transform;
		};
	}
}

#endif
