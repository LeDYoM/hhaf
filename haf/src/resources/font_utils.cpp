#include "resources/font_utils.hpp"
#include <haf/include/resources/ifont.hpp>

using namespace haf;
using namespace haf::res;
using namespace htps;

namespace haf::res
{
FontUtils::FontUtils(IFont* const font) : font_{font}
{}

vector<Rectf32> FontUtils::getTextBoxes(str const& text) const
{
    if (text.empty())
    {
        return {};
    }

    // Take it into account for multilines
//    const f32 vspace{font_->getLineSpacing()};
    f32 x{0.f};
    f32 y{0.0F};  // static_cast<f32>(characterSize)};

    // Create one quad for each character
    u32 prevChar{0U};
    vector<Rectf32> result(text.size());

    for (auto curChar : text)
    {
        // Apply the kerning offset
        x += font_->getKerning(prevChar, curChar);
        prevChar = curChar;

        Rectf32 letterBox{font_->getBounds(curChar) +
                                vector2df{x, y}};
        // TODO: This is because the SFML bug printing at 0.
        letterBox += vector2df{0.0F, 50.0F};


        result.emplace_back(std::move(letterBox));

        // Advance to the next character
        x += font_->getAdvance(curChar);
    }
    return result;
}

Rectf32 FontUtils::textSize(htps::str const& text) const
{
    auto const boxes{getTextBoxes(text)};
    Rectf32 result{};
    for (auto const& box : boxes)
    {
        result.left = std::min(result.left, box.left);
        result.setRight(std::max(result.right(), box.right()));
        result.top = std::min(result.top, box.top);
        result.setBottom(std::max(result.bottom(), box.bottom()));
    }
    return result;
}

}  // namespace haf::res
