#include <haf/shareddata/include/shareddata.hpp>
#include <haf/shareddata/i_include/shareddatasystem.hpp>
#include <system/i_include/systemprovider.hpp>
#include <system/i_include/get_system.hpp>

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
