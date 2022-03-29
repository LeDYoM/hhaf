#include "resources/font_utils.hpp"
#include <haf/include/resources/ifont.hpp>

using namespace haf;
using namespace haf::res;
using namespace htps;

namespace haf::res
{
FontUtils::FontUtils(IFont* const font) : font_{font}
{}

TextRenderData FontUtils::getTextRenderData(str const& text) const
{
    if (text.empty())
    {
        return {};
    }

    // Create one quad for each character
    u32 prevChar{0U};
    TextRenderData result(text.size());
    f32 current_character_position_x{0.0F};

    for (auto curChar : text)
    {
        CharacterRenderData character_render_data{};

        // Apply the kerning offset
        current_character_position_x += font_->getKerning(prevChar, curChar);

        prevChar                               = curChar;
        character_render_data.characterBounds  = font_->getBounds(curChar);
        character_render_data.characterAdvance = font_->getAdvance(curChar);

        current_character_position_x +=
            character_render_data.characterBounds.left;

        current_character_position_x +=
            character_render_data.characterBounds.width / 2.0F;

        character_render_data.character_position.x =
            current_character_position_x;
        character_render_data.character_size =
            character_render_data.characterBounds.size();

        result.character_render_data.push_back(character_render_data);

        current_character_position_x -=
            character_render_data.characterBounds.width / 2.0F;

        current_character_position_x += character_render_data.characterAdvance;

        result.text_size.x += character_render_data.characterAdvance;

        if (result.text_size.y < character_render_data.characterBounds.height)
        {
            result.text_size.y = character_render_data.characterBounds.height;
        }
    }

    for (auto& character_render_data : result.character_render_data)
    {
        auto bounds{character_render_data.characterBounds.height / 2.0F};
        auto half_size_y{result.text_size.y / 2.0F};
        character_render_data.character_position.y =
            half_size_y + ((half_size_y - bounds));
    }

    return result;
}

}  // namespace haf::res
