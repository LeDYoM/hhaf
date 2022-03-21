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

    for (auto curChar : text)
    {
        CharacterRenderData character_render_data{};

        // Apply the kerning offset
        //        x += font_->getKerning(prevChar, curChar);
        prevChar                               = curChar;
        character_render_data.characterBounds  = font_->getBounds(curChar);
        character_render_data.characterAdvance = font_->getAdvance(curChar);
        result.character_render_data.emplace_back(
            std::move(character_render_data));

        if (character_render_data.characterAdvance > result.maxCharacterSize.x)
        {
            result.maxCharacterSize.x = character_render_data.characterAdvance;
        }

        if (character_render_data.characterBounds.size().y >
            result.maxCharacterSize.y)
        {
            result.maxCharacterSize.y =
                character_render_data.characterBounds.size().y;
        }

        result.text_size.x += character_render_data.characterAdvance;
    }

    result.text_size.y = result.maxCharacterSize.y;
    return result;
}

}  // namespace haf::res
