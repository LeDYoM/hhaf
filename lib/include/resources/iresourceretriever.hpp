#pragma once

#ifndef LIB_IRESOURCERETRIVER_INCLUDE_HPP
#define LIB_IRESOURCERETRIVER_INCLUDE_HPP

#include <mtypes/include/str.hpp>
#include <mtypes/include/types.hpp>

namespace lib::scene
{
    class ITTFont;
    class ITexture;
    class IShader;
}

namespace lib
{
    class IResourceRetriever
    {
    public:
        virtual sptr<scene::ITTFont> getFont(const str &rid) = 0;
        virtual sptr<scene::ITexture> getTexture(const str &rid) = 0;
        virtual sptr<scene::IShader> getShader(const str &rid) = 0;
    };
}

#endif
