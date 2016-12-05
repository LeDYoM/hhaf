#ifndef LIB_DRAW_RENDERSTATES_INCLUDE_HPP__
#define LIB_DRAW_RENDERSTATES_INCLUDE_HPP__

#include "transformation.hpp"
#include "texture.hpp"

#include <lib/include/types.hpp>

#include <SFML/Graphics/RenderStates.hpp>

#include <stack>

namespace lib
{
	namespace draw
	{
		class RenderStates
		{
		public:
			RenderStates();
			~RenderStates();

			sf::RenderStates &internalStates() { return m_renderStates; }
			void newFrame();
			sf::RenderStates prepareNewElement(const Transform &transform, sptr<Texture> texture);
			sf::RenderStates prepareNewElement(const Transform &transform, const sf::Texture* texture);
			void pushChanges(const Transform &transform);
			void popChanges();
		private:
			sf::RenderStates m_renderStates;
			std::stack<sf::RenderStates> m_statesStack;
		};
	}
}

#endif
