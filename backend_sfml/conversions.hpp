#include <htypes/include/cast.hpp>
#include "renderwindow.hpp"
#include <backend_dev/include/ikey.hpp>
#include <backend_dev/include/itexture.hpp>
#include <backend_dev/include/ishader.hpp>
#include <backend_dev/include/icamera.hpp>
#include "sfml_texture.hpp"
#include "sfml_shader.hpp"
#include "sfml_2d_camera.hpp"
#include <SFML/Window.hpp>
#include <SFML/System/String.hpp>

namespace haf::backend::sfmlb
{
template <typename T>
constexpr sf::Rect<T> to_sf_type(htps::Rect<T> const& rect) noexcept
{
    return sf::Rect<T>{rect.left, rect.top, rect.width, rect.height};
}

template <typename T>
constexpr htps::Rect<T> from_sf_type(sf::Rect<T> const& rect) noexcept
{
    return htps::Rect<T>{rect.left, rect.top, rect.width, rect.height};
}

template <typename T>
constexpr const sf::Vector2<T> to_sf_type(htps::vector2d<T> const& v) noexcept
{
    return sf::Vector2<T>{v.x, v.y};
}

template <typename T>
constexpr const htps::vector2d<T> from_sf_type(sf::Vector2<T> const& v) noexcept
{
    return htps::vector2d<T>{v.x, v.y};
}

constexpr IKey doCast(sf::Keyboard::Key const& k) noexcept
{
    return static_cast<IKey>(k);
}

inline auto to_sf_type(htps::str const& other) noexcept
{
    return sf::String{other.c_str()};
}

inline auto to_sf_type(char const* const other) noexcept
{
    return sf::String{other};
}

inline sf::Transform to_sf_type(htps::f32 const* const matrix) noexcept
{
    return sf::Transform{matrix[0U], matrix[4U], matrix[12U],
                         matrix[1U], matrix[5U], matrix[13U],
                         matrix[3U], matrix[7U], matrix[15U]};
}

constexpr sf::Texture const* to_sf_type(ITexture const* texture) noexcept
{
    if (texture != nullptr)
    {
        if (auto const sf_texture{htps::d_cast<SFMLTexture const*>(texture)})
        {
            return sf_texture->backEndTexture();
        }
    }
    return nullptr;
}

constexpr sf::Shader const* to_sf_type(IShader const* const shader) noexcept
{
    if (shader != nullptr)
    {
        if (auto const sf_shader{htps::d_cast<SFMLShader const*>(shader)})
        {
            return sf_shader->backEndShader();
        }
    }
    return nullptr;
}

inline auto to_sf_type(iVertex const* const vertex) noexcept
{
    return reinterpret_cast<sf::Vertex const* const>(vertex);
}

inline auto to_sf_type(iVertex const vertex) noexcept
{
    return sf::Vertex{sf::Vector2f{vertex.pos_x, vertex.pos_y},
                      sf::Color{vertex.r, vertex.g, vertex.b, vertex.a},
                      sf::Vector2f{vertex.tc_x, vertex.tc_y}};
}

inline auto to_sf_type(iColor const& color) noexcept
{
    return sf::Color{color.r, color.g, color.b, color.a};
}

inline auto to_sf_type(htps::f32 const* const matrix,
                       ITexture const* const texture,
                       IShader const* const shader) noexcept
{
    return sf::RenderStates{sf::RenderStates::Default.blendMode,
                            to_sf_type(matrix), to_sf_type(texture),
                            to_sf_type(shader)};
}

inline SFML2DCamera* to_sf_type(ICamera * const camera)
{
    return dynamic_cast<SFML2DCamera*>(camera);
}

}  // namespace haf::backend::sfmlb
