#include "../iwindow.hpp"
#include "renderwindow.hpp"
#include "ttfontfactory.hpp"
#include "texturefactory.hpp"
#include "../interfaces.hpp"

/*
lib::backend::IWindow * __stdcall createWindow() {
	return new lib::backend::sfmlb::RenderWindow;
}
*/

lib::backend::ITTFontFactory * __stdcall createTTFontFactory() {
	return new lib::backend::sfmlb::TTFontFactory;
}
/*
lib::backend::ITextureFactory * __stdcall createTextureFactory() {
	return new lib::backend::sfmlb::TextureFactory;
}
*/
