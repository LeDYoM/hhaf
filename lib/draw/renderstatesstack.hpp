#ifndef LIB_DRAW_RENDERSTATES_INCLUDE_HPP__
#define LIB_DRAW_RENDERSTATES_INCLUDE_HPP__

#pragma  once

#include "texture.hpp"

#include <lib/include/types.hpp>

#include <SFML/Graphics/RenderStates.hpp>

#include <stack>

namespace lib
{
	namespace draw
	{
		class Transform;
		class Texture;
		class RenderStatesStack;
		class RenderStatesStackHandle final
		{
		public:
			~RenderStatesStackHandle();
		private:
			constexpr RenderStatesStackHandle(RenderStatesStack &stack);
			RenderStatesStack &m_stack;
			friend class RenderStatesStack;
		};

		class RenderStatesStack final
		{
		public:
			RenderStatesStack();
			~RenderStatesStack();

			sf::RenderStates const &internalStates() const { return m_renderStates; }
			void newFrame() noexcept;
			RenderStatesStackHandle pushChanges(const Transform *transform, const Texture *texture);
			void popChanges();
		private:
			sf::RenderStates m_renderStates;
			std::stack<sf::RenderStates> m_statesStack;
			friend class RenderStatesStackHandle;
		};
	}
}

#endif
