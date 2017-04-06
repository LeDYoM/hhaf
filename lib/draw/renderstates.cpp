#include <SFML/Graphics/RenderStates.hpp>
#include <cstddef>
#include "renderstates.hpp"

namespace lib
{
	namespace draw
	{
		RenderStates::RenderStates() : RenderStates{ {}, {} } {	}

		RenderStates::RenderStates(const Transform & transform, const Texture *texture)
			: m_transform{transform}, m_texture{texture} {}
	}
}
