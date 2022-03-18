#include "resources/font_utils.hpp"
#include <haf/include/resources/ifont.hpp>

using namespace haf;
using namespace haf::res;
using namespace htps;

namespace haf::res
{
FontUtils::FontUtils(IFont* const font) : font_{font}
{}

vector<CharacterRenderData> FontUtils::getTextRenderData(str const& text) const
{
    if (text.empty())
    {
        return {};
    }

    // Take it into account for multilines
    //    const f32 vspace{font_->getLineSpacing()};
    f32 x{0.0F};
    f32 y{0.0F};  // static_cast<f32>(characterSize)};

    // Create one quad for each character
    u32 prevChar{0U};
    vector<CharacterRenderData> result(text.size());

    for (auto curChar : text)
    {
        CharacterRenderData character_render_data{};

        // Apply the kerning offset
        x += font_->getKerning(prevChar, curChar);
        prevChar = curChar;

        character_render_data.characterBounds = font_->getBounds(curChar);
        character_render_data.characterBox =
            character_render_data.characterBounds + vector2df{x, y};
        result.emplace_back(std::move(character_render_data));

        // Advance to the next character
        x += font_->getAdvance(curChar);
    }
    return result;
}

Rectf32 FontUtils::textSize(htps::str const& text) const
{
    auto const text_render_data{getTextRenderData(text)};
    Rectf32 result{};
    for (auto&& chrd : text_render_data)
    {
        result.left = std::min(result.left, chrd.characterBox.left);
        result.setRight(std::max(result.right(), chrd.characterBox.right()));
        result.top = std::min(result.top, chrd.characterBox.top);
        result.setBottom(std::max(result.bottom(), chrd.characterBox.bottom()));
    }
    return result;
}

}  // namespace haf::res
