#ifndef HAF_BACKEND_IRESOURCE_FACTORIES_INCLUDE_HPP
#define HAF_BACKEND_IRESOURCE_FACTORIES_INCLUDE_HPP

#include "iresourcefactory.hpp"

namespace haf::backend
{
class ITexture;
class ITTFont;
class IBMPFont;
}  // namespace haf::backend

namespace haf::backend
{
using ITextureFactory = IResourceFactory<ITexture>;
using ITTFontFactory  = IResourceFactory<ITTFont>;
using IBMPFontFactory = IResourceFactory<IBMPFont>;
}  // namespace haf::backend

#endif
