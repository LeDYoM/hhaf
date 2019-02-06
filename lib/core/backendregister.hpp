#pragma once

#ifndef LIB_BACKEND_REGISTER_HPP
#define LIB_BACKEND_REGISTER_HPP

#include <lib/include/backend/iwindow.hpp>
#include <lib/include/backend/iresourcefactories.hpp>
#include <lib/include/backend/interfaces.hpp>

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
	private:
		IInfoFactory* info_factory_;
		IWindowFactory* window_factory_;
		ITTFontFactoryFactory* ttfont_factory_factory_;
		ITextureFactoryFactory* texture_factory_factory_;
		IShaderFactoryFactory* shader_factory_factory_;
	};
}

#endif
