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
			constexpr Vertex(const vector2df &p, const Color &c, const vector2df &tc) noexcept : position{ p }, color{ c }, texCoords{ tc } {}
			constexpr Vertex(const vector2df &p, const vector2df &tc) noexcept : position{ p }, color{}, texCoords{ tc } {}
			constexpr Vertex() noexcept = default;
			constexpr Vertex(Vertex&&) noexcept = default;
			Vertex& operator=(Vertex&&) noexcept = default;
			constexpr Vertex(const Vertex&) noexcept = default;
			Vertex& operator=(const Vertex&) noexcept = default;
			vector2df position;
			Color color;
			vector2df texCoords;
		};
	}
}

#endif
