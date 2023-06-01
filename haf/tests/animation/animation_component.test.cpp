#include "catch.hpp"

#include <htypes/include/types.hpp>
#include <haf/include/animation/animation_component.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::anim;

namespace
{
struct CommonData
{
    sptr<AnimationComponent> animation_component;
};
}  // namespace

TEST_CASE("haf::anim::AnimationComponent", "[AnimationComponent][Component]")
{
    //    constexpr u32 Start_State  = 0U;
    //    constexpr u32 Finish_State = 1U;

    CommonData common;
    common.animation_component = msptr<AnimationComponent>();
//    common.animation_component->update();
}
