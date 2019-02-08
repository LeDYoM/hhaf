#include <lib/include/backend/iwindow.hpp>
#include <lib/include/backend/interfaces.hpp>

#include "renderwindow.hpp"
#include "ttfontfactory.hpp"
#include "texturefactory.hpp"
#include "shaderfactory.hpp"

#ifdef _WIN32
    #define EXPORT   extern "C" __declspec( dllexport )
#else
    #define EXPORT   extern "C"
#endif

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

EXPORT lib::backend::IShaderFactory * createShaderFactory() {
    return new lib::backend::sfmlb::ShaderFactory;
}

EXPORT bool destroyShaderFactory(lib::backend::IShaderFactory *isf) {
    if (isf) {
        delete isf;
        return true;
    }
    return false;
}

using WindowBackendInfo = lib::backend::DefaultFactoryOf
	<lib::backend::IWindowProviderInfo,
	lib::backend::sfmlb::WindowBackendInfo>;

using WindowFactory = lib::backend::DefaultFactoryOf
	<lib::backend::IWindow,
	lib::backend::sfmlb::RenderWindow>;

using TTFontFactoryFactory = lib::backend::DefaultFactoryOf
	<lib::backend::ITTFontFactory,
	lib::backend::sfmlb::TTFontFactory>;

using TextureFactoryFactory = lib::backend::DefaultFactoryOf
	<lib::backend::ITextureFactory,
	lib::backend::sfmlb::TextureFactory>;

using ShaderFactoryFactory = lib::backend::DefaultFactoryOf
	<lib::backend::IShaderFactory,
	lib::backend::sfmlb::ShaderFactory>;

struct BackendManager
{
	WindowBackendInfo *window_backend_info_factory_{ nullptr };
	WindowFactory *window_factory_{ nullptr };
	TTFontFactoryFactory *ttfont_factory_factory_{ nullptr };
	TextureFactoryFactory *texture_factory_factory_{ nullptr };
	ShaderFactoryFactory *shader_factory_factory_{ nullptr };

	void create()
	{
		window_backend_info_factory_ = new WindowBackendInfo;
		window_factory_ = new WindowFactory;
		ttfont_factory_factory_ = new TTFontFactoryFactory;
		texture_factory_factory_ = new TextureFactoryFactory;
		shader_factory_factory_ = new ShaderFactoryFactory;
	}

	void setFactories(lib::backend::IBackendRegister*const backend_register)
	{
		backend_register->setFactory(window_backend_info_factory_);
		backend_register->setFactory(window_factory_);
		backend_register->setFactory(ttfont_factory_factory_);
		backend_register->setFactory(texture_factory_factory_);
		backend_register->setFactory(shader_factory_factory_);
	}

	void resetFactories(lib::backend::IBackendRegister*const backend_register)
	{
		backend_register->setFactory(static_cast<WindowBackendInfo*>(nullptr));
		backend_register->setFactory(static_cast<WindowFactory*>(nullptr));
		backend_register->setFactory(static_cast<TTFontFactoryFactory*>(nullptr));
		backend_register->setFactory(static_cast<TextureFactoryFactory*>(nullptr));
		backend_register->setFactory(static_cast<ShaderFactoryFactory*>(nullptr));
	}

	template <typename T>
	void SecureDeleteRawPointer(T*& pnt)
	{
		if (pnt)
		{
			delete pnt;
			pnt = nullptr;
		}
	}

	void destroy()
	{
		SecureDeleteRawPointer(window_backend_info_factory_);
		SecureDeleteRawPointer(window_factory_);
		SecureDeleteRawPointer(ttfont_factory_factory_);
		SecureDeleteRawPointer(texture_factory_factory_);
		SecureDeleteRawPointer(shader_factory_factory_);
	}

	~BackendManager()
	{
		destroy();
	}
};

BackendManager *backend_manager{ nullptr };

EXPORT bool init_lib(lib::backend::IBackendRegister*const ibackend_register)
{
	if (!backend_manager)
	{
		backend_manager = new BackendManager;
		backend_manager->create();

		backend_manager->setFactories(ibackend_register);
		return true;
	}
	return false;
}

EXPORT bool finish_lib(lib::backend::IBackendRegister*const ibackend_register)
{
	if (backend_manager)
	{
		backend_manager->resetFactories(ibackend_register);
		backend_manager->destroy();
		delete backend_manager;
		backend_manager = nullptr;
		return true;
	}

	return false;
}
