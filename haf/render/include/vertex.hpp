#ifndef HAF_SCENE_VERTEX_INCLUDE_HPP
#define HAF_SCENE_VERTEX_INCLUDE_HPP

#include <htypes/include/vector2d.hpp>
#include <haf/scene/include/color.hpp>

namespace haf::scene
{
struct Vertex final
{
    constexpr Vertex(htps::vector2df p, Color c, htps::vector2df tc) noexcept :
        position{std::move(p)}, color{std::move(c)}, texCoords{std::move(tc)}
    {}
    constexpr Vertex(htps::vector2df p, htps::vector2df tc) noexcept :
        position{std::move(p)}, color{}, texCoords{std::move(tc)}
    {}
    constexpr Vertex() noexcept         = default;
    constexpr Vertex(Vertex&&) noexcept = default;
    Vertex& operator=(Vertex&&) noexcept     = default;
    constexpr Vertex(const Vertex&) noexcept = default;
    Vertex& operator=(const Vertex&) noexcept = default;
    htps::vector2df position{};
    Color color{};
    htps::vector2df texCoords{};
};

}  // namespace haf::scene

#endif
