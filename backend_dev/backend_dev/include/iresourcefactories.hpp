#pragma once

#ifndef LIB_BACKEND_IRESOURCEFACTORIES_INCLUDE_HPP
#define LIB_BACKEND_IRESOURCEFACTORIES_INCLUDE_HPP

#include <mtypes/include/str.hpp>

#include "iresourcefactory.hpp"
#include "itexture.hpp"
#include "ittfont.hpp"
#include "ishader.hpp"
#include "ibmpfont.hpp"

namespace lib::backend
{
    using ITextureFactory = IResourceFactory<ITexture>;
    using ITTFontFactory = IResourceFactory<ITTFont>;
    using IShaderFactory = IResourceFactory<IShader>;
    using IBMPFontFactory = IResourceFactory<IBMPFont>;
}

#endif
