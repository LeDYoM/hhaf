#pragma once

#ifndef LIB_IRESOURCERETRIVER_INCLUDE_HPP
#define LIB_IRESOURCERETRIVER_INCLUDE_HPP

#include <mtypes/include/str.hpp>
#include <mtypes/include/types.hpp>

namespace lib
{
    namespace scene
    {
        class TTFont;
        class Texture;
        class Shader;
    }

    class IResourceRetriever
    {
    public:
        virtual sptr<scene::TTFont> getFont(const str &rid) = 0;
        virtual sptr<scene::Texture> getTexture(const str &rid) = 0;
        virtual sptr<scene::Shader> getShader(const str &rid) = 0;
    };
}

#endif
