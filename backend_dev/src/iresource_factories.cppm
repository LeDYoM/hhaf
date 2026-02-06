export module backend_dev:iresource_factories;

import :iresource_factory;

namespace haf::backend
{
class ITexture;
class ITTFont;
class IShader;
class IBMPFont;
}  // namespace haf::backend

namespace haf::backend
{
export using ITextureFactory = IResourceFactory<ITexture>;
export using ITTFontFactory  = IResourceFactory<ITTFont>;
export using IShaderFactory  = IResourceFactory<IShader>;
export using IBMPFontFactory = IResourceFactory<IBMPFont>;
}  // namespace haf::backend
