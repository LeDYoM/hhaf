#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#ifndef HAF_FRESOURCES_FONTUTILS_INCLUDE_HPP
#define HAF_FRESOURCES_FONTUTILS_INCLUDE_HPP

#include <haf/include/resources/ifont.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/rect.hpp>
#include <htypes/include/str.hpp>
#include "text_render_data.hpp"

namespace haf::res
{
class IFont;
}

namespace haf::res
{
class FontUtils
{
public:
    FontUtils(res::IFont* const font);
    TextRenderData getTextRenderData(htps::str const& text) const;

private:
    res::IFont* const font_;
};

}  // namespace haf::res

#endif
