#include <backend/include/backend_register.hpp>
#include "backend_utils.hpp"

using namespace htps;

namespace haf::backend
{
BackendRegister::BackendRegister(htps::str const& module_name) :
    module_name_{module_name}
{}

void BackendRegister::setFactory(uptr<IWindowFactory> window_factory) noexcept
{
    window_factory_ = htps::move(window_factory);
}

void BackendRegister::setLibFuncs(
    p_initBackendClient init_lib_func,
    p_finishBackendClient finish_lib_func) noexcept
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

bool BackendRegister::fillRegisteredFactories()
{
    return fillFactories(this, &window_);

}  // namespace haf::backend

bool BackendRegister::emptyRegisteredFactories()
{
    return emptyFactories(this, &window_);
}

htps::str const& BackendRegister::moduleName() const noexcept
{
    return module_name_;
}

}  // namespace haf::backend
