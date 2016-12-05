#ifndef LIB_DRAW_RENDERSTATES_INCLUDE_HPP__
#define LIB_DRAW_RENDERSTATES_INCLUDE_HPP__

#include <SFML/Graphics/RenderStates.hpp>


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

		private:
			sf::RenderStates m_renderStates;
		};
	}
}

#endif
