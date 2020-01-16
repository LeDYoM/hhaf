#pragma once

#ifndef LIB_SCENE_BMPFONTPRIVATE_INCLUDE_HPP
#define LIB_SCENE_BMPFONTPRIVATE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/resources/include/ifont.hpp>
#include <lib/resources/include/texture.hpp>

namespace lib::scene
{
    struct KearningInfo
    {
        KearningInfo(const u32 second_, const s32 amount_) 
            : second{second_}, amount{amount_}	{ }
        KearningInfo() = default;
        u32 second;
        s32 amount;
    };

    struct CharDescriptor
    {
        Rect<u16> position;
        vector2d<s16> offset;
        s16 xadvance;
        s16 page;
        vector<KearningInfo> kearn;
        Rectf32 offsetedPosition;

        constexpr s32 GetKerningPair(const u32 second) const
        {
            const auto iterator(kearn.cfind_if([second](const auto& this_kearn)
            { return this_kearn.second == second; }));

            return iterator == kearn.cend() ? 0 : iterator->amount;        
        }
    };

    struct PageData
    {
        str file;
        sptr<Texture> it;
    };

    struct FontInfo
    {
        str face;
        u16 size;
        bool bold;
        bool italic;
        str charset;
        bool unicode;
        f32 stretchH;
        bool smooth;
        bool aa;
        Rect<s16> padding;
        vector2d<s16> spacing;
        bool outline;
    };

    class BMFontPrivate
    {
    public:
        s16 lineHeight;
        s16 base;
        vector2du32 size_;
        s16 pages;
        s16 outline;
        FontInfo fInfo;
        f32 adv;
        vector<CharDescriptor> chars_;
        vector<PageData> pagesData_;

        static void advanceCharPos(vector2d<f32> &nextCharPos, const CharDescriptor *charDescriptor, const char *nextChar)
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
