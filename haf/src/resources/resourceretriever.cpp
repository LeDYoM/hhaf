#include <haf/include/resources/resourceretriever.hpp>
#include "resourcemanager.hpp"
#include "system/get_system.hpp"

using namespace htps;
using namespace haf::sys;

namespace haf::res
{
sptr<ITTFont> ResourceRetriever::getTTFont(const htps::str& rid) const
{
    return getSystem<ResourceManager>(attachedNode()).getTTFont(rid);
}

sptr<ITexture> ResourceRetriever::getTexture(const htps::str& rid) const
{
    return getSystem<ResourceManager>(attachedNode()).getTexture(rid);
}

sptr<IShader> ResourceRetriever::getShader(const htps::str& rid) const
{
    return getSystem<ResourceManager>(attachedNode()).getShader(rid);
}

sptr<IFont> ResourceRetriever::getBMPFont(const htps::str& rid) const
{
    return getSystem<ResourceManager>(attachedNode()).getBMPFont(rid);
}

}  // namespace haf::res
