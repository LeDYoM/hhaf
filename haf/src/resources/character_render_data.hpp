#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#ifndef HAF_RESOURCES_CHARACTER_RENDER_DATA_INCLUDE_HPP
#define HAF_RESOURCES_CHARACTER_RENDER_DATA_INCLUDE_HPP

#include <htypes/include/rect.hpp>
#include <htypes/include/vector.hpp>

namespace haf::res
{
struct CharacterRenderData
{
    htps::Rectf32 characterBounds;
    htps::f32 characterAdvance;

    bool operator==(CharacterRenderData const& rhs) const noexcept
    {
        return characterBounds == rhs.characterBounds &&
            characterAdvance == rhs.characterAdvance;
    }
};

}  // namespace haf::res

#endif