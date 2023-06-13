#ifndef HAF_BACKEND_REGISTER_INCLUDE_HPP
#define HAF_BACKEND_REGISTER_INCLUDE_HPP

#include <backend_dev/include/iwindow.hpp>
#include <backend_dev/include/ibackendregister.hpp>

using p_initBackendClient =
    bool (*)(haf::backend::client::IBackendRegister* const);
using p_finishBackendClient =
    bool (*)(haf::backend::client::IBackendRegister* const);

namespace haf::backend
{
class BackendRegister final : public client::IBackendRegister
{
public:
    explicit BackendRegister(htps::str const& module_name);
    void setFactory(htps::uptr<IWindowFactory>) noexcept override;

    void setLibFuncs(p_initBackendClient init_lib_func,
                     p_finishBackendClient finish_lib_func) noexcept;

    template <typename T,
              typename = std::enable_if_t<std::is_same_v<T, IWindowFactory>>>
    htps::sptr<IWindowFactory> getFactory()
    {
        return window_factory_;
    }

    bool init();
    bool finish();

    inline bool canUse() const noexcept
    {
        return init_lib_func_ != nullptr && finish_lib_func_ != nullptr;
    }

    bool fillRegisteredFactories();
    bool emptyRegisteredFactories();

    htps::str const& moduleName() const noexcept;
    htps::rptr<IWindow> window_{nullptr};

private:
    htps::str module_name_{};
    p_initBackendClient init_lib_func_{nullptr};
    p_finishBackendClient finish_lib_func_{nullptr};
    htps::sptr<IWindowFactory> window_factory_;
};
}  // namespace haf::backend

#endif
