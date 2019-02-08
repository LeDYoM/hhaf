#include "backendregister.hpp"
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

	void BackendRegister::setLibFuncs(p_initLib init_lib_func, p_finishLib finish_lib_func) noexcept
	{
		init_lib_func_ = init_lib_func;
		finish_lib_func_ = finish_lib_func;
	}

	bool BackendRegister::init()
	{
		if (canUse())
		{
			const bool result{ init_lib_func_(this) };
			assert_debug(result, "Cannot initialize library");
			return result;
		}
		return false;
	}

	bool BackendRegister::finish()
	{
		if (finish_lib_func_)
		{
			return finish_lib_func_(this);
		}
		return false;
	}
}
