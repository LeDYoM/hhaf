#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#ifndef HAF_FRESOURCES_CHARACTER_RENDER_DATA_INCLUDE_HPP
#define HAF_FRESOURCES_CHARACTER_RENDER_DATA_INCLUDE_HPP

#include <htypes/include/rect.hpp>

namespace haf::res
{
struct CharacterRenderData
{
    htps::Rectf32 characterBounds;
    htps::Rectf32 characterBox;

    bool operator==(CharacterRenderData const& rhs) const noexcept
    {
        return characterBounds == rhs.characterBounds &&
            characterBox == rhs.characterBox;
    }
};

}  // namespace haf::res

#endif