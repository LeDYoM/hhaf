#pragma once

#ifndef HAF_SCENE_BMPFONTPRIVATE_INCLUDE_HPP
#define HAF_SCENE_BMPFONTPRIVATE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/resources/include/ifont.hpp>
#include <lib/resources/include/itexture.hpp>

namespace haf::scene
{
    struct KearningInfo
    {
        KearningInfo(const mtps::u32 second_, const mtps::s32 amount_) 
            : second{second_}, amount{amount_}	{ }
        KearningInfo() = default;
        mtps::u32 second;
        mtps::s32 amount;
    };

    struct CharDescriptor
    {
        mtps::Rect<mtps::u16> position;
        mtps::vector2d<mtps::s16> offset;
        mtps::s16 xadvance;
        mtps::s16 page;
        mtps::vector<KearningInfo> kearn;
        mtps::Rectf32 offsetedPosition;

        constexpr mtps::s32 GetKerningPair(const mtps::u32 second) const
        {
            const auto iterator(kearn.cfind_if([second](const auto& this_kearn)
            { return this_kearn.second == second; }));

            return iterator == kearn.cend() ? 0 : iterator->amount;        
        }
    };

    struct PageData
    {
        mtps::str file;
        mtps::sptr<ITexture> it;
    };

    struct FontInfo
    {
        mtps::str face;
        mtps::u16 size;
        bool bold;
        bool italic;
        mtps::str charset;
        bool unicode;
        mtps::f32 stretchH;
        bool smooth;
        bool aa;
        mtps::Rect<mtps::s16> padding;
        mtps::vector2d<mtps::s16> spacing;
        bool outline;
    };

    class BMFontPrivate
    {
    public:
        mtps::s16 lineHeight;
        mtps::s16 base;
        mtps::vector2du32 size_;
        mtps::s16 pages;
        mtps::s16 outline;
        FontInfo fInfo;
        mtps::f32 adv;
        mtps::vector<CharDescriptor> chars_;
        mtps::vector<PageData> pagesData_;

        static void advanceCharPos(mtps::vector2df &nextCharPos, const CharDescriptor *charDescriptor, const char *nextChar)
        {
            if (nextChar)
            {
                nextCharPos.x += charDescriptor->GetKerningPair(*nextChar);
            }

            nextCharPos.x += charDescriptor->xadvance;
        }
    };
}

#endif
