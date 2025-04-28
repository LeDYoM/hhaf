HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_TEXT_BASE_SIZE_INCLUDE_HPP
#define HAF_SCENE_TEXT_BASE_SIZE_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <htypes/include/types.hpp>
#include <facil_math/include/vector2d.hpp>
#include <htypes/include/str.hpp>

namespace haf::scene
{
class HAF_API TextBaseSize
{
public:
    TextBaseSize() noexcept;
    TextBaseSize(char const ch, htps::size_type const size);

    TextBaseSize(htps::str text);
    TextBaseSize(fmath::vector2df size);
    TextBaseSize(htps::str text, fmath::vector2df size);

    bool operator==(TextBaseSize const& rhs) const noexcept;

    htps::str const& text() const noexcept;
    fmath::vector2df value() const noexcept;

private:
    htps::str m_text;
    fmath::vector2df m_value;
};

}  // namespace haf::scene

#endif
