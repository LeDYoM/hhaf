#include "renderwindow.hpp"
#include <lib/include/key.hpp>
#include <lib/backend/itexture.hpp>
#include "texture.hpp"
#include "texturettfont.hpp"
#include <SFML/Window.hpp>
#include <SFML/System/String.hpp>

namespace lib::backend::sfmlb
{
    template <typename T>
    constexpr const sf::Rect<T> fromRect(const Rect<T> &rect) noexcept { return sf::Rect<T>{rect.left, rect.top, rect.width, rect.height}; }

    template <typename T>
    constexpr const Rect<T> toRect(const sf::Rect<T> &rect) noexcept { return Rect<T>{rect.left, rect.top, rect.width, rect.height}; }

    template <typename T>
    constexpr const sf::Vector2<T> fromVector2d(const vector2d<T> &v) noexcept { return sf::Vector2<T>{v.x, v.y}; }

    template <typename T>
    constexpr const vector2d<T> toVector2d(const sf::Vector2<T> &v) noexcept { return vector2d<T>{v.x, v.y}; }

    constexpr input::Key doCast(const sf::Keyboard::Key &k) noexcept
    {
        return static_cast<input::Key>((int)k);
    }

    inline sf::String getAsString(const str& other) noexcept
    {
//        std::wstring wsTmp(other.cbegin(), other.cend());
        return sf::String(other.c_str());
    }

    inline sf::Transform asTransform(const f32* matrix) noexcept
    {
        return sf::Transform{ matrix[0], matrix[4], matrix[12],
            matrix[1], matrix[5], matrix[13],
            matrix[3], matrix[7], matrix[15] };

    }

    constexpr const sf::Texture *const asTexture(const ITexture*t)
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

    inline const sf::RenderStates asRenderStates(const f32 *matrix, const ITexture *texture) noexcept
    {
        return sf::RenderStates(sf::RenderStates::Default.blendMode,
            asTransform(matrix),
            asTexture(texture),
            nullptr);
    }
}
