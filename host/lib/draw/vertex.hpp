#ifndef LIB_DRAW_VERTEX_HPP
#define LIB_DRAW_VERTEX_HPP

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include <lib/draw/color.hpp>

namespace lib
{
	namespace draw
	{
		class Vertex
		{
		public:
			constexpr Vertex(const vector2df &p, const Color &c, const vector2df &tc) : position{ p }, color{ c }, texCoords{ tc } {}
			constexpr Vertex() : Vertex({}, {}, {}) {}
			vector2df position;
			Color color{ colors::White };
			vector2df texCoords;
		};
	}
}

#endif
