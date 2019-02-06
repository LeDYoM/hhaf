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


namespace lib::backend
{

	template <typename T>
	class FactoryOf
	{
	public:
		virtual T *const create() noexcept = 0;
		virtual bool destroy(T *) noexcept = 0;
		virtual ~FactoryOf() {}
	};

	using IInfoFactory = FactoryOf<IWindowProviderInfo>;
	using IWindowFactory = FactoryOf<IWindow>;
	using ITTFontFactoryFactory = FactoryOf<ITTFontFactory>;
	using ITextureFactoryFactory = FactoryOf<ITextureFactory>;
	using IShaderFactoryFactory = FactoryOf<IShaderFactory>;

	class IBackendRegister
	{
	public:
		virtual void setFactory(IInfoFactory* const) noexcept = 0;
		virtual void setFactory(IWindowFactory* const) noexcept = 0;
		virtual void setFactory(ITTFontFactoryFactory* const) noexcept = 0;
		virtual void setFactory(ITextureFactoryFactory* const) noexcept = 0;
		virtual void setFactory(IShaderFactoryFactory* const) noexcept = 0;
		virtual ~IBackendRegister() {}
	};
}

using p_initLib = void (*)(lib::backend::IBackendRegister* const);
using p_finishLib = void(*)(lib::backend::IBackendRegister* const);

#endif
