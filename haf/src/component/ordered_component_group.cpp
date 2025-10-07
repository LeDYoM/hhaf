#include <haf/include/component/ordered_component_group.hpp>

using namespace htps;

namespace haf::component
{
bool OrderedComponentGroup::InsertAtIndex(core::u32 const index,
                                          core::sptr<Component>&&)
{
    if (BaseClass::size() < index)
    {
        BaseClass::resize(index + 1U);
    }
    return true;
}

}  // namespace haf::component
