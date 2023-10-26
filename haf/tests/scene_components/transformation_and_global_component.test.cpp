#include "catch.hpp"

#include <haf/include/core/types.hpp>
#include <haf/include/scene_components/global_transformation_component.hpp>
#include <haf/include/scene_components/transformation_component.hpp>

#include "system_test_utils.hpp"
#include "component_test_utils.hpp"

using namespace haf;
using namespace haf::test;
using namespace haf::scene;
using namespace haf::core;
using namespace haf::component;
/*
TEST_CASE("TransformationAndGlobalComponent::TransformationAndGlobalComponent",
          "[TransformationComponent][scene][component]")
{
    auto test_data{createComponentForTest<TransformationComponent>()};
    auto transformableComponent{test_data.component};
    CHECK(transformableComponent != nullptr);
}

TEST_CASE("TransformationAndGlobalComponent::DefaultValues",
          "[TransformationAndGlobalComponent][scene][component]")
{
    auto test_data{createComponentForTest<TransformationComponent>()};
    auto transformableComponent{test_data.component};
    CHECK(transformableComponent != nullptr);

    CHECK(transformableComponent->hasPendingMatrixUpdate());
    test_data.system.rootSceneNode()->componentContainer().updateComponents(
        TransformationComponent::StaticSceneUpdateTime);
    CHECK_FALSE(transformableComponent->hasPendingMatrixUpdate());
}

TEST_CASE("TransformationAndGlobalComponent::SimpleTransformation",
          "[TransformationComponent][scene][component]")
{
    auto test_data{createComponentForTest<TransformationComponent>()};
    auto transformableComponent{test_data.component};
    CHECK(transformableComponent != nullptr);

    CHECK(transformableComponent->hasPendingMatrixUpdate());
    test_data.system.rootSceneNode()->componentContainer().updateComponents(
        TransformationComponent::StaticSceneUpdateTime);
    CHECK_FALSE(transformableComponent->hasPendingMatrixUpdate());

    transformableComponent->Position = {2.0F, 2.0F};
    CHECK(transformableComponent->hasPendingMatrixUpdate());
    test_data.system.rootSceneNode()->componentContainer().updateComponents(
        TransformationComponent::StaticSceneUpdateTime);
    CHECK_FALSE(transformableComponent->hasPendingMatrixUpdate());

    transformableComponent->Scale = {2.0F, 2.0F};
    CHECK(transformableComponent->hasPendingMatrixUpdate());
    test_data.system.rootSceneNode()->componentContainer().updateComponents(
        TransformationComponent::StaticSceneUpdateTime);
    CHECK_FALSE(transformableComponent->hasPendingMatrixUpdate());

    transformableComponent->Rotation = {2.0F, 2.0F};
    CHECK(transformableComponent->hasPendingMatrixUpdate());
    test_data.system.rootSceneNode()->componentContainer().updateComponents(
        TransformationComponent::StaticSceneUpdateTime);
    CHECK_FALSE(transformableComponent->hasPendingMatrixUpdate());
}
*/
