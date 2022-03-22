#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#ifndef HAF_RESOURCES_TEXT_RENDER_DATA_INCLUDE_HPP
#define HAF_RESOURCES_TEXT_RENDER_DATA_INCLUDE_HPP

#include <htypes/include/rect.hpp>
#include <htypes/include/vector.hpp>
#include "character_render_data.hpp"

namespace haf::res
{
struct TextRenderData
{
    htps::vector<CharacterRenderData> character_render_data;
    htps::vector2df text_size{};
    htps::vector2df maxCharacterSize;

    TextRenderData() = default;
    explicit TextRenderData(htps::size_type const size) :
        character_render_data(size)
    {}

    bool operator==(TextRenderData const& rhs) const noexcept
    {
        return character_render_data == rhs.character_render_data &&
            text_size == rhs.text_size;
    }

    htps::f32 getProportionSize(htps::size_type const index_char) const
    {
        return character_render_data[index_char].characterAdvance /
            maxCharacterSize.x;
    }
};

}  // namespace haf::res

#endif