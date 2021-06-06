#include "catch.hpp"

#include <htypes/include/types.hpp>
#include <haf/include/scene_components/animationcomponent.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;

namespace
{
struct CommonData
{
    sptr<AnimationComponent> animation_component;
};
}

TEST_CASE("haf::scene::AnimationComponent",
          "[StatesController][lib][scene][component][AnimationComponent][IComponent]")
{
//    constexpr u32 Start_State  = 0U;
//    constexpr u32 Finish_State = 1U;

    CommonData common;
    common.animation_component = msptr<AnimationComponent>();
    common.animation_component->update();

}
