#pragma once

#ifndef LIB_IRESOURCEHANDLER_INCLUDE_HPP
#define LIB_IRESOURCEHANDLER_INCLUDE_HPP

#include <mtypes/include/str.hpp>
#include <mtypes/include/types.hpp>

namespace lib::scene
{
class BMPFont;
class TTFont;
class Texture;
class IShader;
} // namespace lib::scene

namespace lib
{
class IResourceHandler
{
public:
    virtual bool loadTTFont(const str &rid, const str &fileName) = 0;
    virtual bool loadTexture(const str &rid, const str &fileName) = 0;
    virtual bool loadShader(const str &rid, const str &fileName) = 0;
    virtual bool loadBMPFont(const str &rid, const str &fileName) = 0;
};
} // namespace lib

#endif
