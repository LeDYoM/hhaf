#pragma once

#ifndef LIB_IRESOURCEHANDLER_INCLUDE_HPP
#define LIB_IRESOURCEHANDLER_INCLUDE_HPP

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

    class IResourceHandler
    {
    public:
        virtual sptr<scene::TTFont> loadFont(const str &rid, const str &fileName) = 0;
        virtual sptr<scene::Texture> loadTexture(const str &rid, const str &fileName) = 0;
        virtual sptr<scene::Shader> loadShader(const str &rid, const str &fileName) = 0;
    };
}

#endif
