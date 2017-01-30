#ifndef LIB_DRAW_GEMOTRYGENERATOR_HPP
#define LIB_DRAW_GEMOTRYGENERATOR_HPP

#pragma once

#include <lib/include/types.hpp>
#include <lib/include/rect.hpp>

namespace lib
{
	namespace draw
	{
		class Font;
		class GeometryGenerator
		{
		public:
			constexpr GeometryGenerator() noexcept = default;

			static vector2df size;
			static Color color;

			BasicVertexArray generateQuad();

			Rectf32 generateShape(const vector2df &size, const u32 granularity = 10);
			Rectf32 generateText(const sptr<Font> &, std::string str, const u32 characterSize,
				const bool bold, const bool underlined, const bool strikeThrough, const bool isItalic);

		};
	}
}

#endif
