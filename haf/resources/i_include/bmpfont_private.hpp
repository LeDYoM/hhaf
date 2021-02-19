#ifndef HAF_SCENE_BMPFONTPRIVATE_INCLUDE_HPP
#define HAF_SCENE_BMPFONTPRIVATE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/resources/include/ifont.hpp>
#include <haf/resources/include/itexture.hpp>

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

    constexpr htps::s32 GetKerningPair(const htps::u32 second) const
    {
        const auto iterator(kearn.cfind_if([second](const auto& this_kearn) {
            return this_kearn.second == second;
        }));

        return iterator == kearn.cend() ? 0 : iterator->amount;
    }
};

struct PageData
{
    htps::str file;
    htps::sptr<ITexture> it;
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

class BMFontPrivate
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

    static void advanceCharPos(htps::vector2df& nextCharPos,
                               const CharDescriptor* charDescriptor,
                               const char* nextChar)
    {
        if (nextChar)
        {
            nextCharPos.x += charDescriptor->GetKerningPair(*nextChar);
        }

        nextCharPos.x += charDescriptor->xadvance;
    }
};
}  // namespace haf::res

#endif
