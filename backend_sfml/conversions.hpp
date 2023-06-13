#include <facil_math/include/rect.hpp>
#include <htypes/include/cast.hpp>
#include <backend_dev/include/ikey.hpp>
#include "sfml_render_window.hpp"
#include <SFML/Window.hpp>
#include <SFML/System/String.hpp>

namespace haf::backend::sfmlb
{
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

}  // namespace haf::backend::sfmlb
