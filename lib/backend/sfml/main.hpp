#pragma once

#ifndef LIB_BACKEND_SFML_MAIN_INCLUDE_HPP__
#define LIB_BACKEND_SFML_MAIN_INCLUDE_HPP__

#include "../iwindow.hpp"
#include "renderwindow.hpp"
#include "ttfontfactory.hpp"
#include "texturefactory.hpp"

namespace lib
{
	namespace backend
	{
		namespace sfmlb
		{
		}
	}
}
/*
lib::backend::IWindow * __stdcall createWindow() {
	return new lib::backend::sfmlb::RenderWindow;
}

lib::backend::ITTFontFactory * __stdcall createTTFontFactory() {
	return new lib::backend::sfmlb::TTFontFactory;
}

lib::backend::ITextureFactory * __stdcall createTextureFactory() {
	return new lib::backend::sfmlb::TextureFactory;
}
*/
#endif
