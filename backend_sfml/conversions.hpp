#include "renderwindow.hpp"
#include <backend_dev/include/ikey.hpp>
#include <backend_dev/include/itexture.hpp>
#include <backend_dev/include/ishader.hpp>
#include "texture.hpp"
#include "shader.hpp"
#include <SFML/Window.hpp>
#include <SFML/System/String.hpp>

namespace haf::backend::sfmlb
{
template <typename T>
constexpr const sf::Rect<T> to_sf_type(const mtps::Rect<T>& rect) noexcept
{
    return sf::Rect<T>{rect.left, rect.top, rect.width, rect.height};
}

template <typename T>
constexpr const mtps::Rect<T> from_sft_type(const sf::Rect<T>& rect) noexcept
{
    return mtps::Rect<T>{rect.left, rect.top, rect.width, rect.height};
}

template <typename T>
constexpr const sf::Vector2<T> to_sf_type(const mtps::vector2d<T>& v) noexcept
{
    return sf::Vector2<T>{v.x, v.y};
}

template <typename T>
constexpr const mtps::vector2d<T> from_sf_type(const sf::Vector2<T>& v) noexcept
{
    return mtps::vector2d<T>{v.x, v.y};
}

constexpr iKey doCast(const sf::Keyboard::Key& k) noexcept
{
    return static_cast<iKey>((int)k);
}

inline sf::String to_sf_type(const mtps::str& other) noexcept
{
    return sf::String(other.c_str());
}

inline sf::String to_sf_type(const char* other) noexcept
{
    return sf::String(other);
}

inline sf::Transform to_sf_type(const mtps::f32* matrix) noexcept
{
    return sf::Transform{matrix[0], matrix[4], matrix[12],
                         matrix[1], matrix[5], matrix[13],
                         matrix[3], matrix[7], matrix[15]};
}

constexpr const sf::Texture* const to_sf_type(const ITexture* t)
{
    if (t)
    {
        if (auto tmp = dynamic_cast<const Texture*>(t))
        {
            return &(tmp->backEndTexture());
        }
    }
    return nullptr;
}

constexpr const sf::Shader* const to_sf_type(const IShader* s)
{
    if (s)
    {
        if (auto tmp = dynamic_cast<const Shader*>(s))
        {
            return &(tmp->backEndShader());
        }
    }
    return nullptr;
}

inline const sf::PrimitiveType to_sf_type(
    const iPrimitiveType primitive_type)
{
    return static_cast<sf::PrimitiveType>(primitive_type);
}

inline const sf::Vertex* to_sf_type(const iVertex* vertex)
{
    return reinterpret_cast<const sf::Vertex*>(vertex);
}

inline const sf::RenderStates to_sf_type(const mtps::f32* matrix,
                                         const ITexture* texture,
                                         const IShader* shader) noexcept
{
    return sf::RenderStates(sf::RenderStates::Default.blendMode,
                            to_sf_type(matrix), to_sf_type(texture),
                            to_sf_type(shader));
}
}  // namespace haf::backend::sfmlb
