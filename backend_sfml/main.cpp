#include <lib/backend/iwindow.hpp>
#include <lib/backend/interfaces.hpp>

#include "renderwindow.hpp"
#include "ttfontfactory.hpp"
#include "texturefactory.hpp"

#define EXPORT extern "C" SPECIFIC_EXPORT

EXPORT lib::backend::IWindowProviderInfo * createWindowProviderInfo() {
	return new lib::backend::sfmlb::WindowBackendInfo;
}

EXPORT bool destroyWindowProviderInfo(lib::backend::IWindowProviderInfo *iwpi) {
	if (iwpi) {
		delete iwpi;
		return true;
	}
	return false;
}


EXPORT lib::backend::IWindow * createWindow() {
	return new lib::backend::sfmlb::RenderWindow;
}

EXPORT bool destroyWindow(lib::backend::IWindow *iw) {
	if (iw) {
		delete iw;
		return true;
	}
	return false;
}


EXPORT lib::backend::ITTFontFactory * createTTFontFactory() {
	return new lib::backend::sfmlb::TTFontFactory;
}

EXPORT bool destroyTTFontFactory(lib::backend::ITTFontFactory *ittff) {
	if (ittff) {
		delete ittff;
		return true;
	}
	return false;
}


EXPORT lib::backend::ITextureFactory * createTextureFactory() {
	return new lib::backend::sfmlb::TextureFactory;
}

EXPORT bool destroyTextureFactory(lib::backend::ITextureFactory *itf) {
	if (itf) {
		delete itf;
		return true;
	}
	return false;
}
