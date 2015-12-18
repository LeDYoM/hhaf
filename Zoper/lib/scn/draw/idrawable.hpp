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
			};
		}
	}
}

#endif
