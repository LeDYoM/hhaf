HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_BMPFONT_PRIVATE_INCLUDE_HPP
#define HAF_RESOURCES_BMPFONT_PRIVATE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <backend_dev/include/ifont.hpp>
#include <backend_dev/include/itexture.hpp>

#include "default_bmp_font.hpp"

using namespace htps;

namespace haf::res
{
struct KearningInfo
{
    htps::u32 second;
    htps::s32 amount;
};

struct CharDescriptor
{
    fmath::Rect<htps::u16> position;
    fmath::vector2d<htps::s16> offset;
    htps::s16 xadvance;
    htps::s16 page;
    htps::vector<KearningInfo> kearn;
    fmath::Rectf32 offsetedPosition;

    htps::s32 GetKerningPair(const htps::u32 second) const;
};

struct PageData
{
    htps::str file;
    backend::ITexture const* texture;
};

struct FontInfo
{
    htps::str face;
    htps::u16 size;
    bool bold;
    bool italic;
    htps::str charset;
    bool unicode;
    htps::f32 stretchH;
    bool smooth;
    bool aa;
    fmath::Rect<htps::s16> padding;
    fmath::vector2d<htps::s16> spacing;
    bool outline;
};

class DefaultBMPFont::DefaultBMFontPrivate
{
public:
    htps::s16 lineHeight;
    htps::s16 base;
    fmath::vector2du32 size_;
    htps::s16 pages;
    htps::s16 outline;
    FontInfo fInfo;
    htps::f32 adv;
    htps::vector<CharDescriptor> chars_;
    htps::vector<PageData> pagesData_;

    bool ParseFont(const str& data);
};

}  // namespace haf::res

#endif
