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
	class IFactoryOf
	{
	public:
		virtual T *const create() noexcept = 0;
		virtual bool destroy(T *) noexcept = 0;
		virtual ~IFactoryOf() {}
	};

	template <typename T, typename ConcreteObject>
	class DefaultFactoryOf : public IFactoryOf<T>
	{
	public:
		virtual T *const create() noexcept override
		{
			return new ConcreteObject;
		}

		virtual bool destroy(T *obj) noexcept override
		{
			delete obj;
			return true;
		}

		virtual ~DefaultFactoryOf() {}
	};

	using IInfoFactory = IFactoryOf<IWindowProviderInfo>;
	using IWindowFactory = IFactoryOf<IWindow>;
	using ITTFontFactoryFactory = IFactoryOf<ITTFontFactory>;
	using ITextureFactoryFactory = IFactoryOf<ITextureFactory>;
	using IShaderFactoryFactory = IFactoryOf<IShaderFactory>;

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

using p_initLib = bool (*)(lib::backend::IBackendRegister* const);
using p_finishLib = bool (*)(lib::backend::IBackendRegister* const);

#endif
