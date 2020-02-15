#include <lib/shareddata/include/shareddataview.hpp>
#include <lib/shareddata/i_include/shareddatasystem.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/system/scenemanager.hpp>
#include <lib/system/systemprovider.hpp>

namespace lib::shdata
{

void SharedData::store(uptr<IShareable> data)
{
    attachedNode()->sceneManager().systemProvider().sharedDataSystem().store(std::move(data));
}

uptr<IShareable> SharedData::retrieve_imp()
{
    log_assert(!isEmpty(), "SharedDataSystem should be empty");
    return attachedNode()->sceneManager().systemProvider().sharedDataSystem().retrieve();
}

bool SharedData::isEmpty()
{
    return attachedNode()->sceneManager().systemProvider().sharedDataSystem().isEmpty();
}

SharedDataView::SharedDataView()
    : data_{nullptr} {}

SharedDataView::~SharedDataView()
{
    log_assert(data_ != nullptr, "Data is nullptr");
    log_assert(attachedNode()->sceneManager().systemProvider().sharedDataSystem().isEmpty(),
               "SharedDataSystem should be empty");

    attachedNode()->sceneManager().systemProvider().sharedDataSystem().store(std::move(data_));

    log_assert(!attachedNode()->sceneManager().systemProvider().sharedDataSystem().isEmpty(),
               "SharedDataSystem should not be empty");

    log_assert(data_ == nullptr, "SharedDataView should contain nullptr");
}

void SharedDataView::onAttached()
{
    log_assert(data_ == nullptr, "SharedDataView should contain nullptr");
    log_assert(!attachedNode()->sceneManager().systemProvider().sharedDataSystem().isEmpty(),
               "SharedDataSystem should not be empty");

    data_ = attachedNode()->sceneManager().systemProvider().sharedDataSystem().retrieve();

    log_assert(attachedNode()->sceneManager().systemProvider().sharedDataSystem().isEmpty(),
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

} // namespace lib::shdata
