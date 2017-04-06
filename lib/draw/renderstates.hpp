#ifndef LIB_DRAW_RENDERSTATES_HPP
#define LIB_DRAW_RENDERSTATES_HPP

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/BlendMode.hpp>
#include <SFML/Graphics/Transform.hpp>

#include <lib/draw/transformation.hpp>
#include <lib/draw/texture.hpp>

#pragma once

namespace sf
{
	class Shader;
	class Texture;
}

namespace lib
{
	namespace draw
	{
		class RenderStates
		{
		public:
			RenderStates();
			RenderStates(const Transform &transform, const Texture *texture);

			Transform      m_transform;
			const Texture *m_texture;

		};
	}
}

#endif
