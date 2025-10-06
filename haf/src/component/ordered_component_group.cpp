#include <haf/include/component/ordered_component_group.hpp>

using namespace htps;

namespace haf::component
{
bool OrderedComponentGroup::InsertAtIndex(core::u32 const index,
                                          core::sptr<Component>&& c)
{
    if (BaseClass::size() < index)
    {
        BaseClass::resize(index + 1U);
        
    }
}

}  // namespace haf::component
