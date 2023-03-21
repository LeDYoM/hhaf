#include <htypes/include/rect.hpp>
#include <htypes/include/cast.hpp>
#include <backend_dev/include/ikey.hpp>
#include <backend_dev/include/itexture.hpp>
#include <backend_dev/include/camera_data.hpp>
#include "sfml_render_window.hpp"
#include "sfml_texture.hpp"
#include <SFML/Window.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transform.hpp>

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

}  // namespace haf::backend::sfmlb
