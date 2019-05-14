#pragma once

#ifndef LIB_SCENE_ITTFONT_INTERFACE_INCLUDE_HPP
#define LIB_SCENE_ITTFONT_INTERFACE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>

#include <lib/include/resources/itexture.hpp>
#include <lib/include/resources/ifont.hpp>

namespace lib::scene
{
	class ITTFont
	{
	public:
		virtual ~ITTFont() {}
		virtual Rectf32 getBounds(const u32 codePoint, const u32 characterSize) const = 0;
		virtual Rectf32 getTextureBounds(const u32 codePoint, const u32 characterSize) const = 0;
		virtual f32 getAdvance(const u32 codePoint, const u32 characterSize) const = 0;
		virtual f32 getLineSpacing(const u32 characterSize) const = 0;
		virtual f32 getKerning(const u32 first, const u32 second, const u32 characterSize) const = 0;
		virtual sptr<ITexture> getTexture(const u32 characterSize) const = 0;
		virtual vector2df textSize(const str& text, const u32 characterSize) const = 0;
		virtual sptr<IFont> font(const u32 charactersize) = 0;
	};
}

#endif
