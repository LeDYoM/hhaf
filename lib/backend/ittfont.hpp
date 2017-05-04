#ifndef LIB_BACKEND_ITTFONT_HPP
#define LIB_BACKEND_ITTFONT_HPP

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include <lib/include/rect.hpp>
#include <lib/draw/hasname.hpp>
#include "itexture.hpp"

namespace lib
{
	namespace backend
	{
		struct ITTGlyph
		{
			Rectf32 bounds;
			Rectf32 textureBounds;
			f32 advance;
		};

		class ITTFont : public core::HasName
		{
		public:
			ITTFont() : core::HasName{ "l" } {}
			using core::HasName::HasName;
			virtual ~ITTFont() {}

			virtual const ITTGlyph getGlyph(u32 codePoint, u32 characterSize, bool bold, f32 outlineThickness) const = 0;
			virtual f32 getLineSpacing(u32 characterSize) const = 0;
			virtual f32 getKerning(u32 first, u32 second, u32 characterSize) const = 0;
			virtual sptr<ITexture> getTexture(u32 characterSize) const = 0;
		};
	}
}
#endif
