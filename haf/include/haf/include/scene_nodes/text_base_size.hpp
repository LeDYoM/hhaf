HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_TEXT_BASE_SIZE_INCLUDE_HPP
#define HAF_SCENE_TEXT_BASE_SIZE_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>
#include <htypes/include/str.hpp>

namespace haf::scene::nodes
{

class HAF_API TextBaseSize
{
public:
    TextBaseSize() noexcept;
    TextBaseSize(char const ch, htps::size_type const size);

    TextBaseSize(htps::str text);
    TextBaseSize(htps::vector2df size);
    TextBaseSize(htps::str text, htps::vector2df size);

    bool operator==(TextBaseSize const& rhs) const noexcept;

    htps::str const& text() const noexcept;
    htps::vector2df value() const noexcept;

private:
    htps::str text_;
    htps::vector2df value_;
};

}  // namespace haf::scene::nodes

#endif
