#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <haf/scene_components/include/animationcomponent.hpp>
#include <haf/scene_components/include/animationcomponent.hpp>

using namespace mtps;
using namespace haf;
using namespace haf::scene;

TEST_CASE("haf::scene::AnimationComponent",
          "[StatesController][lib][scene][component][AnimationComponent][IComponent]")
{
    constexpr u32 Start_State  = 0U;
    constexpr u32 Finish_State = 1U;

    struct CommonData
    {
        sptr<AnimationComponent> animation_component;
    };

    CommonData common;
    common.animation_component = msptr<AnimationComponent>();
    common.animation_component->update();

}
