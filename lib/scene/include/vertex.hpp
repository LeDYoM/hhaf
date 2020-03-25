#pragma once

#ifndef LIB_SCENE_VERTEX_INCLUDE_HPP__
#define LIB_SCENE_VERTEX_INCLUDE_HPP__

#include <mtypes/include/vector2d.hpp>
#include <lib/scene/include/color.hpp>

namespace lib::scene
{
struct Vertex final
{
    constexpr Vertex(mtps::vector2df p, Color c, mtps::vector2df tc) noexcept : position{std::move(p)}, color{std::move(c)}, texCoords{std::move(tc)} {}
    constexpr Vertex(mtps::vector2df p, mtps::vector2df tc) noexcept : position{std::move(p)}, color{}, texCoords{std::move(tc)} {}
    constexpr Vertex() noexcept = default;
    constexpr Vertex(Vertex &&) noexcept = default;
    Vertex &operator=(Vertex &&) noexcept = default;
    constexpr Vertex(const Vertex &) noexcept = default;
    Vertex &operator=(const Vertex &) noexcept = default;
    mtps::vector2df position{};
    Color color{};
    mtps::vector2df texCoords{};
};

static_assert(std::is_standard_layout_v<Vertex>, "Vertex must have the standard layout");
} // namespace lib::scene

#endif
