#pragma once

#ifndef LIB_BACKEND_INTERFACES_INLUDE_HPP
#define LIB_BACKEND_INTERFACES_INLUDE_HPP

#include "iwindow.hpp"
#include "iresourcefactories.hpp"

using p_createWindowProviderInfo = lib::backend::IWindowProviderInfo * (*)();
using p_destroyWindowProviderInfo = bool(*)(lib::backend::IWindowProviderInfo *);

using p_createWindow = lib::backend::IWindow * (*)();
using p_destroyWindow = bool (*)(lib::backend::IWindow *);

using p_createTTFontFactory = lib::backend::ITTFontFactory * (*)();
using p_destroyTTFontFactory = bool (*)(lib::backend::ITTFontFactory *);

using p_createTextureFactory = lib::backend::ITextureFactory * (*)();
using p_destroyTextureFactory = bool (*)(lib::backend::ITextureFactory *);

using p_createShaderFactory = lib::backend::IShaderFactory * (*)();
using p_destroyShaderFactory = bool(*)(lib::backend::IShaderFactory *);

#endif
