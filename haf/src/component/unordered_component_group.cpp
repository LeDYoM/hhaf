#include <haf/include/component/unordered_component_group.hpp>

using namespace htps;

namespace haf::component
{

void UnorderedComponentGroup::PushBack(sptr<Component>&& c)
{
    BaseClass::push_back(core::move(c));
}

void UnorderedComponentGroup::PushBack(sptr<Component> const& c)
{
    BaseClass::push_back(c);
}

}  // namespace haf::component
