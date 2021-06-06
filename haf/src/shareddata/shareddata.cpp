#include <haf/include/shareddata/shareddata.hpp>

#include "shareddata/shareddatasystem.hpp"
#include "system/systemprovider.hpp"
#include "system/get_system.hpp"

#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::shdata
{
bool SharedData::store(Address const& address, IShareable const& data)
{
    return sys::getSystem<sys::SharedDataSystem>(attachedNode())
        .store(address, data);
}

bool SharedData::retrieve(Address const& address, IShareable& data)
{
    return sys::getSystem<sys::SharedDataSystem>(attachedNode())
        .retrieve(address, data);
}

bool SharedData::isEmpty()
{
    return sys::getSystem<sys::SharedDataSystem>(attachedNode()).isEmpty();
}

bool SharedData::makeEmpty()
{
    return sys::getSystem<sys::SharedDataSystem>(attachedNode()).makeEmpty();
}

}  // namespace haf::shdata
