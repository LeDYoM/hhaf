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
			inline const Transform& transform() const noexcept { return m_transform; }
			void updateTransform() noexcept;

			Property<vector2df> origin;
			Property<f32> rotation;
			Property<vector2df> scale;
			Property<vector2df> position;
		private:
			Transform m_transform;
		};
	}
}

#endif
