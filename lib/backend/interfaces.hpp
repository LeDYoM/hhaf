#pragma once

#ifndef LIB_BACKEND_SFML_MAIN_INCLUDE_HPP__
#define LIB_BACKEND_SFML_MAIN_INCLUDE_HPP__

#include "iwindow.hpp"
#include "ittfontfactory.hpp"
#include "itexturefactory.hpp"

/*
lib::backend::IWindow * __stdcall createWindow() {
	return new lib::backend::sfmlb::RenderWindow;
}
*/

lib::backend::ITTFontFactory * __stdcall createTTFontFactory();

/*
lib::backend::ITextureFactory * __stdcall createTextureFactory() {
	return new lib::backend::sfmlb::TextureFactory;
}
*/
#endif
