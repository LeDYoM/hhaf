#pragma once

#ifndef LIB_SCENE_BMPFONTPRIVATE_INCLUDE_HPP
#define LIB_SCENE_BMPFONTPRIVATE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/include/resources/ifont.hpp>
#include "texture.hpp"

namespace lib::scene
{
    class KearningInfo
    {
    public:
        u32 second;
        s32 amount;
        KearningInfo(u32 second_, s32 amount_) : second(second_), amount(amount_)	{ }
        KearningInfo() : second(0), amount(0)	{ }
    };

    class CharDescriptor
    {
    public:
        CharDescriptor() = default;
        CharDescriptor(const CharDescriptor&) = default;
        CharDescriptor& operator=(const CharDescriptor&) = default;

        Rect<u16> position;
        vector2d<s16> offset;
        s16 xadvance;
        s16 page;
        vector<KearningInfo> kearn;
        Rectf32 offsetedPosition;
//        VertexArray charTriangles;
//        mlp<VAOWrapper> charVAO;
        s32 GetKerningPair(const u8 &second) const
        {
            for (u32 j = 0; j < kearn.size(); ++j)
            {
                if (kearn[j].second == second)
                {
                    return kearn[j].amount;
                }
            }
            return 0;
        }
        
    };

    class PageData
    {
    public:
        str file;
        PageData() : file("") {}
        sptr<Texture> it;

        PageData(str file_) :file(std::move(file_)),it(nullptr) {}
    };
    class FontInfo
    {
    public:
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
