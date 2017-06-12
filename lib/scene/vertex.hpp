#ifndef LIB_DRAW_VERTEX_HPP
#define LIB_DRAW_VERTEX_HPP

#pragma once

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <lib/scene/color.hpp>

namespace lib
{
	namespace scene
	{
		struct Vertex final
		{
			constexpr Vertex(vector2df p, Color c, vector2df tc) noexcept : position{ std::move(p) }, color{ std::move(c) }, texCoords{ std::move(tc) } {}
			constexpr Vertex(vector2df p, vector2df tc) noexcept : position{ std::move(p) }, color{}, texCoords{ std::move(tc) } {}
			constexpr Vertex() = default;
			constexpr Vertex(Vertex&&) noexcept = default;
			Vertex& operator=(Vertex&&) noexcept = default;
			constexpr Vertex(const Vertex&) noexcept = default;
			Vertex& operator=(const Vertex&) noexcept = default;
			vector2df position;
			Color color;
			vector2df texCoords;
		};

		static_assert(std::is_standard_layout<Vertex>::value, "Vertex must have the standard layout");
	}
}

#endif
