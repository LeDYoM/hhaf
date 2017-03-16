#ifndef LIB_DRAW_VERTEX_HPP
#define LIB_DRAW_VERTEX_HPP

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include <lib/draw/color.hpp>

namespace lib
{
	namespace draw
	{
		struct Vertex
		{
			constexpr Vertex(vector2df p, Color c, vector2df tc) noexcept : position{ std::move(p) }, color{ std::move(c) }, texCoords{ std::move(tc) } {}
			constexpr Vertex(vector2df p, vector2df tc) noexcept : position{ std::move(p) }, color{}, texCoords{ std::move(tc) } {}
			constexpr Vertex() = default;
			constexpr Vertex(Vertex&&) = default;
			Vertex& operator=(Vertex&&) noexcept = default;
			constexpr Vertex(const Vertex&) = default;
			Vertex& operator=(const Vertex&) noexcept = default;
			vector2df position;
			Color color;
			vector2df texCoords;
//			int a;
		};

//		static_assert(std::is_pod<Vertex>::value, "Vertex is not a pod");
	}
}

#endif
