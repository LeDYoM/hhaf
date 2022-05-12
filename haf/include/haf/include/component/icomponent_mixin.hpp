HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_ICOMPONENT_MIXIN_INCLUDE_HPP
#define HAF_SCENE_ICOMPONENT_MININ_INCLUDE_HPP

#include <haf/include/component/icomponent.hpp>

namespace haf::component
{
template <typename T1, typename T2>
class IComponentMixin : public IComponent
{
    virtual void update() override
    {
        T1::update();
        T2::update();
    }
};
}  // namespace haf::component

#endif
