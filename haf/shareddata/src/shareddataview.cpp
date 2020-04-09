#include <haf/shareddata/include/shareddataview.hpp>
#include <haf/shareddata/i_include/shareddatasystem.hpp>
#include <haf/system/i_include/systemprovider.hpp>
#include <haf/system/i_include/get_system.hpp>
#include <haf/include/liblog.hpp>

using namespace mtps;

namespace haf::shdata
{
void SharedData::store(uptr<IShareable> data)
{
    sys::getSystem<sys::ISharedDataSystem>(attachedNode()).store(std::move(data));
}

uptr<IShareable> SharedData::retrieve_imp()
{
    log_assert(!isEmpty(), "SharedDataSystem should be empty");
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
    log_assert(data_ != nullptr, "Data is nullptr");
    log_assert(sys::getSystem<sys::ISharedDataSystem>(attachedNode()).isEmpty(),
               "SharedDataSystem should be empty");

    sys::getSystem<sys::ISharedDataSystem>(attachedNode()).store(std::move(data_));

    log_assert(!sys::getSystem<sys::ISharedDataSystem>(attachedNode()).isEmpty(),
               "SharedDataSystem should not be empty");

    log_assert(data_ == nullptr, "SharedDataView should contain nullptr");
}

void SharedDataView::onAttached()
{
    log_assert(data_ == nullptr, "SharedDataView should contain nullptr");
    log_assert(!sys::getSystem<sys::ISharedDataSystem>(attachedNode()).isEmpty(),
               "SharedDataSystem should not be empty");

    data_ = sys::getSystem<sys::ISharedDataSystem>(attachedNode()).retrieve();

    log_assert(sys::getSystem<sys::ISharedDataSystem>(attachedNode()).isEmpty(),
               "SharedDataSystem should be empty");
    log_assert(data_ != nullptr, "Data is nullptr");
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
