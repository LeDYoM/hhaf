#include "shareddataview.hpp"
#include "shareddatasystem.hpp"
#include <system/i_include/systemprovider.hpp>
#include <system/i_include/get_system.hpp>

#include <hlog/include/hlog.hpp>

using namespace mtps;

namespace haf::shdata
{
void SharedData::store(uptr<IShareable> data)
{
    sys::getSystem<sys::ISharedDataSystem>(attachedNode()).store(std::move(data));
}

uptr<IShareable> SharedData::retrieve_imp()
{
    LogAsserter::log_assert(!isEmpty(), "SharedDataSystem should be empty");
    return sys::getSystem<sys::ISharedDataSystem>(attachedNode()).retrieve();
}

bool SharedData::isEmpty()
{
    return sys::getSystem<sys::ISharedDataSystem>(attachedNode()).isEmpty();
}

SharedDataView::SharedDataView()
    : data_{nullptr} {}

SharedDataView::~SharedDataView()
{
    LogAsserter::log_assert(data_ != nullptr, "Data is nullptr");
    LogAsserter::log_assert(sys::getSystem<sys::ISharedDataSystem>(attachedNode()).isEmpty(),
               "SharedDataSystem should be empty");

    sys::getSystem<sys::ISharedDataSystem>(attachedNode()).store(std::move(data_));

    LogAsserter::log_assert(!sys::getSystem<sys::ISharedDataSystem>(attachedNode()).isEmpty(),
               "SharedDataSystem should not be empty");

    LogAsserter::log_assert(data_ == nullptr, "SharedDataView should contain nullptr");
}

void SharedDataView::onAttached()
{
    LogAsserter::log_assert(data_ == nullptr, "SharedDataView should contain nullptr");
    LogAsserter::log_assert(!sys::getSystem<sys::ISharedDataSystem>(attachedNode()).isEmpty(),
               "SharedDataSystem should not be empty");

    data_ = sys::getSystem<sys::ISharedDataSystem>(attachedNode()).retrieve();

    LogAsserter::log_assert(sys::getSystem<sys::ISharedDataSystem>(attachedNode()).isEmpty(),
               "SharedDataSystem should be empty");
    LogAsserter::log_assert(data_ != nullptr, "Data is nullptr");
}

IShareable &SharedDataView::data()
{
    return *(data_.get());
}

const IShareable &SharedDataView::data() const
{
    return *(data_.get());
}

} // namespace haf::shdata
