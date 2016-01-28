#ifndef __LIB_IDRAWABLE_HPP__
#define __LIB_IDRAWABLE_HPP__

#include "../../types.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Drawable.hpp>

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
			class IDrawable : private sf::Drawable
			{
			public:
				IDrawable() {}
				virtual ~IDrawable() {}

				virtual u32 draw(lib::core::Window *window, sf::RenderStates &states);
				virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

				inline bool isVisible() const { return visible; }
				inline void setVisible(bool nv) { visible = nv; }
			protected:
				bool visible{ true };
			};
		}
	}
}

#endif
