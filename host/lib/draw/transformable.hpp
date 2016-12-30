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
			const vector2df& getPosition() const;
			const Transform& getTransform() const noexcept;
			void updateTransform();

			Property<vector2df> origin;
			Property<f32> rotation;
			Property<vector2df> scale;
		private:
			vector2df m_position;
			Transform m_transform;
		};
	}
}

#endif
