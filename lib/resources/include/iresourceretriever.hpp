#pragma once

#ifndef LIB_IRESOURCERETRIVER_INCLUDE_HPP
#define LIB_IRESOURCERETRIVER_INCLUDE_HPP

#include <mtypes/include/str.hpp>
#include <mtypes/include/types.hpp>

namespace lib::scene
{
    class IFont;
    class ITTFont;
    class ITexture;
    class IShader;
}

namespace lib
{
    class IResourceRetriever
    {
    public:
        virtual mtps::sptr<scene::ITTFont> getTTFont(const mtps::str &rid) = 0;
        virtual mtps::sptr<scene::ITexture> getTexture(const mtps::str &rid) = 0;
        virtual mtps::sptr<scene::IShader> getShader(const mtps::str &rid) = 0;
        virtual mtps::sptr<scene::IFont> getBMPFont(const mtps::str &rid) = 0;
    };
}

#endif
