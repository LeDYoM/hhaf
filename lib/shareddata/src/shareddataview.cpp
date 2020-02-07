#include <lib/shareddata/include/shareddataview.hpp>

namespace lib::shdata
{

void SharedDataView::store(uptr<IShareable>)
{
}

uptr<IShareable> SharedDataView::retrieve()
{
    return nullptr;
}

} // namespace lib::scene
