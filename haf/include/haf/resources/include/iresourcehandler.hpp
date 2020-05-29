#pragma once

#ifndef HAF_IRESOURCEHANDLER_INCLUDE_HPP
#define HAF_IRESOURCEHANDLER_INCLUDE_HPP

#include <mtypes/include/str.hpp>
#include <mtypes/include/types.hpp>

namespace haf::scene
{
class BMPFont;
class TTFont;
class Texture;
class IShader;
}  // namespace haf::scene

namespace haf
{
class IResourceHandler
{
public:
    virtual bool loadTTFont(const mtps::str& rid,
                            const mtps::str& fileName)  = 0;
    virtual bool loadTexture(const mtps::str& rid,
                             const mtps::str& fileName) = 0;
    virtual bool loadShader(const mtps::str& rid,
                            const mtps::str& fileName)  = 0;
    virtual bool loadBMPFont(const mtps::str& rid,
                             const mtps::str& fileName) = 0;
};
}  // namespace haf

#endif
