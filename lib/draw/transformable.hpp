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
			const Transform& getTransform() const noexcept;
			void updateTransform();

			TriggerProperty<vector2df> origin;
			TriggerProperty<f32> rotation;
			TriggerProperty<vector2df> scale;
			TriggerProperty<vector2df> position;
		private:
			Transform m_transform;
		};
	}
}

#endif
