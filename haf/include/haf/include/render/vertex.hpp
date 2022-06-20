HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_VERTEX_INCLUDE_HPP
#define HAF_RENDER_VERTEX_INCLUDE_HPP

#include <htypes/include/vector2d.hpp>
#include <haf/include/scene/color.hpp>

namespace haf::render
{
struct Vertex final
{
    constexpr Vertex(htps::vector2df p,
                     scene::Color c,
                     htps::vector2df tc) noexcept :
        position{htps::move(p)}, color{htps::move(c)}, texCoords{htps::move(tc)}
    {}

    constexpr Vertex(htps::vector2df p, htps::vector2df tc) noexcept :
        position{htps::move(p)}, color{}, texCoords{htps::move(tc)}
    {}

    constexpr Vertex() noexcept         = default;
    constexpr Vertex(Vertex&&) noexcept = default;
    constexpr Vertex& operator=(Vertex&&) noexcept = default;
    constexpr Vertex(Vertex const&) noexcept       = default;
    constexpr Vertex& operator=(Vertex const&) noexcept = default;

    htps::vector2df position{};
    scene::Color color{};
    htps::vector2df texCoords{};
};

}  // namespace haf::render

#endif
