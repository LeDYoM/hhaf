#pragma once

#ifndef LIB_BACKEND_SFML_MAIN_INCLUDE_HPP__
#define LIB_BACKEND_SFML_MAIN_INCLUDE_HPP__

#include "iwindow.hpp"
#include "ittfontfactory.hpp"
#include "itexturefactory.hpp"
/*
lib::backend::IWindowProviderInfo * __stdcall createWindowProviderInfo();
__declspec(dllexport) lib::backend::IWindow * __stdcall createWindow();
lib::backend::ITTFontFactory * __stdcall createTTFontFactory();
lib::backend::ITextureFactory * __stdcall createTextureFactory();
*/
using p_createWindowProviderInfo = lib::backend::IWindowProviderInfo * (*)();
using p_createWindow = lib::backend::IWindow * (*)();
using p_createTTFontFactory = lib::backend::ITTFontFactory * (*)();
using p_createTextureFactory = lib::backend::ITextureFactory * (*)();

/*
__declspec(dllexport) int __stdcall abc();
__declspec(dllexport) int def();
*/
#endif
