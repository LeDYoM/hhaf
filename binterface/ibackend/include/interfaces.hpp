#pragma once

#ifndef LIB_BACKEND_SFML_MAIN_INCLUDE_HPP__
#define LIB_BACKEND_SFML_MAIN_INCLUDE_HPP__

#include "iwindow.hpp"
#include "ittfontfactory.hpp"
#include "itexturefactory.hpp"

using p_createWindowProviderInfo = lib::backend::IWindowProviderInfo * (*)();
using p_destroyWindowProviderInfo = bool(*)(lib::backend::IWindowProviderInfo *);

using p_createWindow = lib::backend::IWindow * (*)();
using p_destroyWindow = bool (*)(lib::backend::IWindow *);

using p_createTTFontFactory = lib::backend::ITTFontFactory * (*)();
using p_destroyTTFontFactory = bool (*)(lib::backend::ITTFontFactory *);

using p_createTextureFactory = lib::backend::ITextureFactory * (*)();
using p_destroyTextureFactory = bool (*)(lib::backend::ITextureFactory *);

#endif
