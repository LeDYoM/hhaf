#ifndef HAF_SCENE_RESOURCES_BMPFONT_PRIVATE_INCLUDE_HPP
#define HAF_SCENE_RESOURCES_BMPFONT_PRIVATE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <haf/include/resources/ifont.hpp>
#include <haf/include/resources/itexture.hpp>

#include "bmpfont.hpp"

using namespace htps;

namespace haf::res
{
struct KearningInfo
{
    KearningInfo(const htps::u32 second_, const htps::s32 amount_) :
        second{second_}, amount{amount_}
    {}
    KearningInfo() = default;
    htps::u32 second;
    htps::s32 amount;
};

struct CharDescriptor
{
    htps::Rect<htps::u16> position;
    htps::vector2d<htps::s16> offset;
    htps::s16 xadvance;
    htps::s16 page;
    htps::vector<KearningInfo> kearn;
    htps::Rectf32 offsetedPosition;

    htps::s32 GetKerningPair(const htps::u32 second) const;
};

struct PageData
{
    htps::str file;
    htps::sptr<ITexture> texture;
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
    htps::Rect<htps::s16> padding;
    htps::vector2d<htps::s16> spacing;
    bool outline;
};

class BMPFont::BMFontPrivate
{
public:
    htps::s16 lineHeight;
    htps::s16 base;
    htps::vector2du32 size_;
    htps::s16 pages;
    htps::s16 outline;
    FontInfo fInfo;
    htps::f32 adv;
    htps::vector<CharDescriptor> chars_;
    htps::vector<PageData> pagesData_;

    bool ParseFont(const str& fontfile);
};

}  // namespace haf::res

#endif
