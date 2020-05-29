#include "shareddata_updater.hpp"
#include "shareddatasystem.hpp"
#include <system/i_include/systemprovider.hpp>
#include <system/i_include/get_system.hpp>

#include <hlog/include/hlog.hpp>

using namespace mtps;

namespace haf::shdata
{
SharedDataUpdater::~SharedDataUpdater()
{
    LogAsserter::log_assert(data_ != nullptr, "Data is nullptr");
    LogAsserter::log_assert(
        sys::getSystem<sys::SharedDataSystem>(attachedNode()).isEmpty(),
        "SharedDataSystem should be empty");

    sys::getSystem<sys::SharedDataSystem>(attachedNode())
        .store(std::move(data_));

    LogAsserter::log_assert(
        !sys::getSystem<sys::SharedDataSystem>(attachedNode()).isEmpty(),
        "SharedDataSystem should not be empty");

    LogAsserter::log_assert(data_ == nullptr,
                            "SharedDataView should contain nullptr");
}

void SharedDataUpdater::onAttached()
{
    LogAsserter::log_assert(data_ == nullptr,
                            "SharedDataView should contain nullptr");
    LogAsserter::log_assert(
        !sys::getSystem<sys::SharedDataSystem>(attachedNode()).isEmpty(),
        "SharedDataSystem should not be empty");

    data_ = sys::getSystem<sys::SharedDataSystem>(attachedNode()).retrieve();

    LogAsserter::log_assert(
        sys::getSystem<sys::SharedDataSystem>(attachedNode()).isEmpty(),
        "SharedDataSystem should be empty");
    LogAsserter::log_assert(data_ != nullptr, "Data is nullptr");
}

IShareable& SharedDataUpdater::data()
{
    return *(data_.get());
}

const IShareable& SharedDataUpdater::data() const
{
    return *(data_.get());
}

}  // namespace haf::shdata
