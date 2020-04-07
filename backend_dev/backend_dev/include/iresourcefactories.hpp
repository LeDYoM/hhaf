#pragma once

#ifndef HAF_BACKEND_IRESOURCEFACTORIES_INCLUDE_HPP
#define HAF_BACKEND_IRESOURCEFACTORIES_INCLUDE_HPP

#include <mtypes/include/str.hpp>

#include "iresourcefactory.hpp"
#include "itexture.hpp"
#include "ittfont.hpp"
#include "ishader.hpp"
#include "ibmpfont.hpp"

namespace haf::backend
{
using ITextureFactory = IResourceFactory<ITexture>;
using ITTFontFactory = IResourceFactory<ITTFont>;
using IShaderFactory = IResourceFactory<IShader>;
using IBMPFontFactory = IResourceFactory<IBMPFont>;
} // namespace haf::backend

#endif
