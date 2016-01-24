#ifndef __LIB_IDRAWABLE_HPP__
#define __LIB_IDRAWABLE_HPP__

#include "../../types.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace lib
{
	namespace core
	{
		class Window;
	}
	namespace scn
	{
		namespace draw
		{
			class IDrawable
			{
			public:
				IDrawable() {}
				virtual ~IDrawable() {}

				virtual void draw(sf::RenderTarget &window, sf::RenderStates &states) const = 0;
				inline bool isVisible() const { return visible; }
				inline void setVisible(bool nv) { visible = nv; }
			protected:
				bool visible{ true };
			};
		}
	}
}

#endif
