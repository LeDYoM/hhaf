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

uptr<IShareable> SharedData::retrieve()
{
    return attachedNode()->sceneManager().systemProvider().sharedDataSystem().retrieve();
}

SharedDataView::SharedDataView()
    : data_{nullptr}
{
}

SharedDataView::~SharedDataView()
{
    attachedNode()->sceneManager().systemProvider().sharedDataSystem().store(std::move(data_));
}

void SharedDataView::onAttached()
{
    data_ = attachedNode()->sceneManager().systemProvider().sharedDataSystem().retrieve();
    log_assert(data_ != nullptr, "Data is nullptr");
}

IShareable &SharedDataView::data()
{
    return *(data_.get());
}

} // namespace lib::shdata
