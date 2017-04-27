#ifndef LIB_DRAW_RENDERSTATES_HPP
#define LIB_DRAW_RENDERSTATES_HPP

#include <lib/draw/transformation.hpp>


#pragma once

namespace lib
{
	namespace draw
	{
		class TextureV1;
		class RenderStates final
		{
		public:
			constexpr RenderStates() : RenderStates{ {},{} } { }
			constexpr RenderStates(const Transform &transform, const TextureV1 *texture)
				: m_transform{ transform }, m_texture{ texture } {}

			constexpr RenderStates(RenderStates &&) noexcept = default;
			RenderStates &operator=(RenderStates&&) noexcept = default;

			Transform m_transform;
			const TextureV1 *m_texture;
		private:
			RenderStates &operator=(const RenderStates&) noexcept = default;
			friend class RenderStatesStack;
		};
	}
}

#endif
