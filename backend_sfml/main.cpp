#include <lib/backend/iwindow.hpp>
#include <lib/backend/interfaces.hpp>

#include "renderwindow.hpp"
#include "ttfontfactory.hpp"
#include "texturefactory.hpp"

#define EXPORT extern "C" __declspec(dllexport)

EXPORT lib::backend::IWindowProviderInfo * createWindowProviderInfo() {
	return new lib::backend::sfmlb::WindowBackendInfo;
}

EXPORT lib::backend::IWindow * createWindow() {
	return new lib::backend::sfmlb::RenderWindow;
}

EXPORT lib::backend::ITTFontFactory * createTTFontFactory() {
	return new lib::backend::sfmlb::TTFontFactory;
}

EXPORT lib::backend::ITextureFactory * createTextureFactory() {
	return new lib::backend::sfmlb::TextureFactory;
}
