#include "renderwindow.hpp"
#include <lib/include/key.hpp>
#include <backend_dev/include/itexture.hpp>
#include "texture.hpp"
#include "texturettfont.hpp"
#include <SFML/Window.hpp>
#include <SFML/System/String.hpp>

namespace lib::backend::sfmlb
{
    template <typename T>
    constexpr const sf::Rect<T> to_sf_type(const Rect<T> &rect) noexcept { return sf::Rect<T>{rect.left, rect.top, rect.width, rect.height}; }

    template <typename T>
    constexpr const Rect<T> from_sft_type(const sf::Rect<T> &rect) noexcept { return Rect<T>{rect.left, rect.top, rect.width, rect.height}; }

    template <typename T>
    constexpr const sf::Vector2<T> to_sf_type(const vector2d<T> &v) noexcept { return sf::Vector2<T>{v.x, v.y}; }

    template <typename T>
    constexpr const vector2d<T> from_sf_type(const sf::Vector2<T> &v) noexcept { return vector2d<T>{v.x, v.y}; }

    constexpr input::Key doCast(const sf::Keyboard::Key &k) noexcept
    {
        return static_cast<input::Key>((int)k);
    }

    inline sf::String to_sf_type(const str& other) noexcept
    {
        return sf::String(other.c_str());
    }

    inline sf::String to_sf_type(const char* other) noexcept
    {
        return sf::String(other);
    }

    inline sf::Transform to_sf_type(const f32* matrix) noexcept
    {
        return sf::Transform{ matrix[0], matrix[4], matrix[12],
            matrix[1], matrix[5], matrix[13],
            matrix[3], matrix[7], matrix[15] };

    }

    constexpr const sf::Texture *const to_sf_type(const ITexture*t)
    {
        if (t) {
            if (auto tmp = dynamic_cast<const Texture*>(t)) {
                return &(tmp->backEndTexture());
            }
            if (auto tmp = dynamic_cast<const TextureTTFont*>(t)) {
                return &(tmp->backEndTexture());
            }
        }
        return nullptr;
    }

    inline const sf::RenderStates to_sf_type(const f32 *matrix, const ITexture *texture) noexcept
    {
        return sf::RenderStates(sf::RenderStates::Default.blendMode,
            to_sf_type(matrix),
            to_sf_type(texture),
            nullptr);
    }
}
