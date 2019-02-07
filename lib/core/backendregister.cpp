#include "backendregister.hpp"

#include <lib/include/core/log.hpp>

namespace lib::backend
{
	void BackendRegister::setFactory(IInfoFactory * const info_factory) noexcept
	{
		info_factory_ = info_factory;
	}

	void BackendRegister::setFactory(IWindowFactory * const window_factory) noexcept
	{
		window_factory_ = window_factory;
	}

	void BackendRegister::setFactory(ITTFontFactoryFactory * const ttfont_factory_factory) noexcept
	{
		ttfont_factory_factory_ = ttfont_factory_factory;
	}

	void BackendRegister::setFactory(ITextureFactoryFactory * const texture_factory_factory) noexcept
	{
		texture_factory_factory_ = texture_factory_factory;
	}

	void BackendRegister::setFactory(IShaderFactoryFactory * const shader_factory_factory) noexcept
	{
		shader_factory_factory_ = shader_factory_factory;
	}
}
