#pragma once

#ifndef LIB_BACKEND_REGISTER_HPP
#define LIB_BACKEND_REGISTER_HPP

#include <backend_dev/include/iwindow.hpp>
#include <backend_dev/include/iresourcefactories.hpp>
#include <backend_dev/include/interfaces.hpp>

namespace lib::backend
{
	class BackendRegister final : public IBackendRegister
	{
	public:
		void setFactory(IInfoFactory* const) noexcept override;
		void setFactory(IWindowFactory* const) noexcept override;
		void setFactory(ITTFontFactoryFactory* const) noexcept override;
		void setFactory(ITextureFactoryFactory* const) noexcept override;
		void setFactory(IShaderFactoryFactory* const) noexcept override;

		void setLibFuncs(p_initLib init_lib_func, 
			p_finishLib finish_lib_func) noexcept;

		template <typename T>
		T* const getFactory() const;

		template <> IInfoFactory* const getFactory() const { return info_factory_; }
		template <> IWindowFactory* const getFactory() const { return window_factory_; }
		template <> ITTFontFactoryFactory* const getFactory() const { return ttfont_factory_factory_; }
		template <> ITextureFactoryFactory* const getFactory() const { return texture_factory_factory_; }
		template <> IShaderFactoryFactory* const getFactory() const { return shader_factory_factory_; }

		bool init();
		bool finish();

		inline bool canUse() const noexcept { return init_lib_func_ != nullptr && finish_lib_func_ != nullptr; }

	private:
		p_initLib init_lib_func_{ nullptr };
		p_finishLib finish_lib_func_{ nullptr };
		IInfoFactory* info_factory_{ nullptr };
		IWindowFactory* window_factory_{ nullptr };
		ITTFontFactoryFactory* ttfont_factory_factory_{ nullptr };
		ITextureFactoryFactory* texture_factory_factory_{ nullptr };
		IShaderFactoryFactory* shader_factory_factory_{ nullptr };
	};
}

#endif
