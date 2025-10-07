#include <haf/include/component/ordered_component_group.hpp>

using namespace haf::core;

namespace haf::component
{
void OrderedComponentGroup::insertAtIndex(u32 const index,
                                          sptr<Component>&& c)
{
    BaseClass::set_at_index(index, core::move(c));
}

void OrderedComponentGroup::insertAtIndex(u32 const index,
                                          sptr<Component> const& c)
{
    BaseClass::set_at_index(index, c);
}

}  // namespace haf::component
