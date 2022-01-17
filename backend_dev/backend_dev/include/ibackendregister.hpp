#ifndef HAF_BACKEND_BACKEND_REGISTER_INLUDE_HPP
#define HAF_BACKEND_BACKEND_REGISTER_INLUDE_HPP

#include <backend_dev/include/iwindow.hpp>
#include <backend_dev/include/irendertarget.hpp>
#include <backend_dev/include/iresourcefactories.hpp>
#include <backend_dev/include/factory_types.hpp>
#include <backend_dev/include/ifactory.hpp>

namespace haf::backend::client
{
class IBackendRegister
{
public:
    virtual void setFactory(htps::uptr<IWindowFactory>) noexcept         = 0;
    virtual void setFactory(htps::uptr<IRenderTargetFactory>) noexcept   = 0;
    virtual void setFactory(htps::uptr<ITTFontFactoryFactory>) noexcept  = 0;
    virtual void setFactory(htps::uptr<ITextureFactoryFactory>) noexcept = 0;
    virtual void setFactory(htps::uptr<IShaderFactoryFactory>) noexcept  = 0;
    virtual void setFactory(htps::uptr<IBMPFontFactoryFactory>) noexcept = 0;

    virtual ~IBackendRegister() {}
};

}  // namespace haf::backend::client

#endif
