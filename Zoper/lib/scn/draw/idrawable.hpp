#ifndef __LIB_IDRAWABLE_HPP__
#define __LIB_IDRAWABLE_HPP__

#include "../../types.hpp"

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

				virtual u32 draw(lib::core::Window *window) const = 0;
				virtual void move(const vector2df&) = 0;
				inline bool isVisible() const { return visible; }
				inline void setVisible(bool nv) { visible = nv; }
			protected:
				bool visible{ true };
			};
		}
	}
}

#endif
