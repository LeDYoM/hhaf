export module backend_dev:factory_types;

import :ifactory;
import :iresource_factories;

namespace haf::backend
{
class IWindow;
}  // namespace haf::backend

namespace haf::backend
{
export using IWindowFactory         = IFactoryOf<IWindow>;
export using ITTFontFactoryFactory  = IFactoryOf<ITTFontFactory>;
export using ITextureFactoryFactory = IFactoryOf<ITextureFactory>;
export using IShaderFactoryFactory  = IFactoryOf<IShaderFactory>;
export using IBMPFontFactoryFactory = IFactoryOf<IBMPFontFactory>;

}  // namespace haf::backend
