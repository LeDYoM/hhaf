#include <haf/include/component/component_updaters.hpp>

namespace haf::component
{
namespace
{
core::u32 asIndex(UpdateTime const updateTime)
{
    return static_cast<core::u32>(updateTime);
}
}  // namespace

ComponentUpdater& ComponentUpdaters::get(UpdateTime const updateTime)
{
    return m_component_updaters[asIndex(updateTime)];
}

}  // namespace haf::component
