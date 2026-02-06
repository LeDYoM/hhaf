export module backend_dev:ibackend_register;

import :iwindow;
import :iresource_factories;
import :factory_types;
import :ifactory;

namespace haf::backend::client
{
export class IBackendRegister
{
public:
    virtual void setFactory(htps::uptr<IWindowFactory>) noexcept         = 0;
    virtual void setFactory(htps::uptr<ITTFontFactoryFactory>) noexcept  = 0;
    virtual void setFactory(htps::uptr<ITextureFactoryFactory>) noexcept = 0;
    virtual void setFactory(htps::uptr<IShaderFactoryFactory>) noexcept  = 0;
    virtual void setFactory(htps::uptr<IBMPFontFactoryFactory>) noexcept = 0;

    virtual ~IBackendRegister() {}
};

}  // namespace haf::backend::client
