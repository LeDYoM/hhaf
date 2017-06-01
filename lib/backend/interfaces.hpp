#pragma once

#ifndef LIB_BACKEND_SFML_MAIN_INCLUDE_HPP__
#define LIB_BACKEND_SFML_MAIN_INCLUDE_HPP__

#include "iwindow.hpp"
#include "ittfontfactory.hpp"
#include "itexturefactory.hpp"

lib::backend::IWindowProviderInfo * __stdcall createWindowProviderInfo();
lib::backend::IWindow * __stdcall createWindow();
lib::backend::ITTFontFactory * __stdcall createTTFontFactory();
lib::backend::ITextureFactory * __stdcall createTextureFactory();

#endif
