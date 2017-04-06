#ifndef LIB_DRAW_RENDERSTATES_HPP
#define LIB_DRAW_RENDERSTATES_HPP

#include <lib/draw/transformation.hpp>


#pragma once

namespace lib
{
	namespace draw
	{
		class Texture;
		class RenderStates final
		{
		public:
			RenderStates();
			RenderStates(const Transform &transform, const Texture *texture);

			Transform m_transform;
			const Texture *m_texture;
		};
	}
}

#endif
