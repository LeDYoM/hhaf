#include "catch.hpp"

#include <haf/include/core/types.hpp>
#include <haf/include/scene_components/global_transformation_component.hpp>

#include "system_test_utils.hpp"
#include "component_test_utils.hpp"

using namespace haf;
using namespace haf::test;
using namespace haf::scene;
using namespace haf::core;
using namespace haf::component;

TEST_CASE("GlobalTransformationComponent::GlobalTransformationComponent",
          "[GlobalTransformationComponent][scene][component]")
{
    auto test_data{createComponentForTest<GlobalTransformationComponent>()};
    auto globalTransformationComponent{test_data.component};
    CHECK(globalTransformationComponent != nullptr);
}
/*
TEST_CASE("GlobalTransformationComponent::DefaultValues",
          "[GlobalTransformationComponent][scene][component]")
{
    auto test_data{createComponentForTest<GlobalTransformationComponent>()};
    auto globalTransformationComponent{test_data.component};
    CHECK(globalTransformationComponent != nullptr);

    CHECK(globalTransformationComponent->hasPendingMatrixUpdate());
    test_data.system.rootSceneNode()->componentContainer().updateComponents();
    CHECK_FALSE(globalTransformationComponent->hasPendingMatrixUpdate());
}
*/