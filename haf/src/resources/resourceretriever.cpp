#include <haf/include/resources/resourceretriever.hpp>
#include "resourcemanager.hpp"
#include "system/get_system.hpp"

using namespace htps;

namespace haf::res
{
sptr<ITTFont> ResourceRetriever::getTTFont(const htps::str& rid) const
{
    return sys::getSystem<sys::ResourceManager>(attachedNode()).getTTFont(rid);
}

sptr<ITexture> ResourceRetriever::getTexture(const htps::str& rid) const
{
    return sys::getSystem<sys::ResourceManager>(attachedNode()).getTexture(rid);
}

sptr<IShader> ResourceRetriever::getShader(const htps::str& rid) const
{
    return sys::getSystem<sys::ResourceManager>(attachedNode()).getShader(rid);
}

sptr<IFont> ResourceRetriever::getBMPFont(const htps::str& rid) const
{
    return sys::getSystem<sys::ResourceManager>(attachedNode()).getBMPFont(rid);
}

}  // namespace haf::res
