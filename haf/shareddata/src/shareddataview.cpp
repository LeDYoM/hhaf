#include "shareddataview.hpp"
#include "shareddatasystem.hpp"
#include <system/i_include/systemprovider.hpp>
#include <system/i_include/get_system.hpp>

#include <hlog/include/hlog.hpp>

using namespace mtps;

namespace haf::shdata
{

const IShareable& SharedDataView::data() const
{
    return *(sys::getSystem<sys::SharedDataSystem>(attachedNode()).view());
}

}  // namespace haf::shdata
