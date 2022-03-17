#ifndef HAF_FRESOURCES_FOUNTUTILS_IMCLUDE_HPP
#define HAF_FRESOURCES_FOUNTUTILS_IMCLUDE_HPP

#include <haf/include/resources/ifont.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/rect.hpp>
#include <htypes/include/str.hpp>

namespace haf::res
{
class IFont;
}

namespace haf::res
{
struct CharacterRenderData
{
    htps::Rectf32 characterBounds;
    htps::Rectf32 characterBox;
};

class FontUtils
{
public:
    FontUtils(res::IFont* const font);
    htps::vector<CharacterRenderData> getTextRenderData(htps::str const& text) const;
    htps::Rectf32 textSize(htps::str const& text) const;

private:
    res::IFont* const font_;
};

}  // namespace haf::res

#endif