HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_CHARACTER_RENDER_DATA_INCLUDE_HPP
#define HAF_RESOURCES_CHARACTER_RENDER_DATA_INCLUDE_HPP

#include <htypes/include/rect.hpp>
#include <htypes/include/vector.hpp>

namespace haf::res
{
struct CharacterRenderData
{
    htps::Rectf32 characterBounds{0.0F, 0.0F, 0.0F, 0.0F};
    htps::f32 characterAdvance{0.0F};
    htps::vector2df character_position{0.0F, 0.0F};
    htps::vector2df character_size{0.0F, 0.0F};

    bool operator==(CharacterRenderData const& rhs) const noexcept
    {
        return characterBounds == rhs.characterBounds &&
            characterAdvance == rhs.characterAdvance &&
            character_position == rhs.character_position &&
            character_size == rhs.character_size;
    }
};

}  // namespace haf::res

#endif