#include <backend/include/backendregister.hpp>

using namespace htps;

namespace haf::backend
{
void BackendRegister::setFactory(uptr<IWindowFactory> window_factory) noexcept
{
    window_factory_ = std::move(window_factory);
}

void BackendRegister::setFactory(
    uptr<IRenderTargetFactory> render_target_factory) noexcept
{
    render_target_factory_ = std::move(render_target_factory);
}

void BackendRegister::setFactory(
    uptr<ITTFontFactoryFactory> ttfont_factory_factory) noexcept
{
    ttfont_factory_factory_ = std::move(ttfont_factory_factory);
}

void BackendRegister::setFactory(
    uptr<ITextureFactoryFactory> texture_factory_factory) noexcept
{
    texture_factory_factory_ = std::move(texture_factory_factory);
}

void BackendRegister::setFactory(
    uptr<IShaderFactoryFactory> shader_factory_factory) noexcept
{
    shader_factory_factory_ = std::move(shader_factory_factory);
}

void BackendRegister::setFactory(
    uptr<IBMPFontFactoryFactory> bmpfont_factory_factory) noexcept
{
    bmpfont_factory_factory_ = std::move(bmpfont_factory_factory);
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
