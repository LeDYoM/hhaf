#include <backend/include/backendregister.hpp>

namespace haf::backend
{
void BackendRegister::setFactory(IWindowFactory* const window_factory) noexcept
{
    window_factory_ = window_factory;
}

void BackendRegister::setFactory(IRenderTargetFactory* const render_target_factory) noexcept
{
    render_target_factory_ = render_target_factory;
}

void BackendRegister::setFactory(
    ITTFontFactoryFactory* const ttfont_factory_factory) noexcept
{
    ttfont_factory_factory_ = ttfont_factory_factory;
}

void BackendRegister::setFactory(
    ITextureFactoryFactory* const texture_factory_factory) noexcept
{
    texture_factory_factory_ = texture_factory_factory;
}

void BackendRegister::setFactory(
    IShaderFactoryFactory* const shader_factory_factory) noexcept
{
    shader_factory_factory_ = shader_factory_factory;
}

void BackendRegister::setFactory(
    IBMPFontFactoryFactory* const bmpfont_factory_factory) noexcept
{
    bmpfont_factory_factory_ = bmpfont_factory_factory;
}

void BackendRegister::setLibFuncs(p_initHaf init_lib_func,
                                  p_finishHaf finish_lib_func) noexcept
{
    init_lib_func_   = init_lib_func;
    finish_lib_func_ = finish_lib_func;
}

bool BackendRegister::init()
{
    if (canUse())
    {
        const bool result{init_lib_func_(this)};
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
}  // namespace haf::backend
