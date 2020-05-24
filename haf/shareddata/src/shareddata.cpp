#include "shareddata.hpp"
#include "shareddatasystem.hpp"
#include <system/i_include/systemprovider.hpp>
#include <system/i_include/get_system.hpp>

#include <hlog/include/hlog.hpp>

using namespace mtps;

namespace haf::shdata
{
bool SharedData::store(uptr<IShareable> data)
{
    return sys::getSystem<sys::SharedDataSystem>(attachedNode())
        .store(std::move(data));
}

uptr<IShareable> SharedData::retrieve_imp()
{
    LogAsserter::log_assert(!isEmpty(), "SharedDataSystem should be empty");
    return sys::getSystem<sys::SharedDataSystem>(attachedNode()).retrieve();
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
