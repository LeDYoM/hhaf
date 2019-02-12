#pragma once

#ifndef LIB_BACKEND_INTERFACES_INLUDE_HPP
#define LIB_BACKEND_INTERFACES_INLUDE_HPP

#include "iwindow.hpp"
#include "iresourcefactories.hpp"

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
