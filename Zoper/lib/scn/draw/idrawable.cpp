#include "idrawable.hpp"
#include "../../core/window.hpp"

namespace lib
{
	namespace scn
	{
		namespace draw
		{

			lib::u32 IDrawable::draw(lib::core::Window *window, sf::RenderStates &states)
			{
				window->draw(*(static_cast<sf::Drawable*>(this)), states);
				return 1;
			}

			void IDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
			{
				throw std::logic_error("The method or operation is not implemented.");
			}

		}
	}
}
