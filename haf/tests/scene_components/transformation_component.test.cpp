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

TEST_CASE("TransformationComponent::TransformationComponent",
          "[TransformationComponent][scene][component]")
{
    auto test_data{createComponentForTest<TransformationComponent>()};
    auto transformableComponent{test_data.component};
    CHECK(transformableComponent != nullptr);
    //    CHECK(
    //        transformableComponent->getComponent<GlobalTransformationComponent>()
    //        != nullptr);
}

TEST_CASE("TransformationComponent::DefaultValues",
          "[TransformationComponent][scene][component]")
{
    auto test_data{createComponentForTest<TransformationComponent>()};
    auto transformableComponent{test_data.component};
    CHECK(transformableComponent != nullptr);
    //    CHECK(
    //        transformableComponent->getComponent<GlobalTransformationComponent>()
    //        != nullptr);

    CHECK(transformableComponent->hasPendingMatrixUpdate());
    test_data.system.rootSceneNode()->componentContainer().updateComponents();
    CHECK_FALSE(transformableComponent->hasPendingMatrixUpdate());
}

TEST_CASE("TransformationComponent::SimpleTransformation",
          "[TransformationComponent][scene][component]")
{
    auto test_data{createComponentForTest<TransformationComponent>()};
    auto transformableComponent{test_data.component};
    CHECK(transformableComponent != nullptr);
    //    CHECK(
    //        transformableComponent->getComponent<GlobalTransformationComponent>()
    //        != nullptr);

    CHECK(transformableComponent->hasPendingMatrixUpdate());
    test_data.system.rootSceneNode()->componentContainer().updateComponents();
    CHECK_FALSE(transformableComponent->hasPendingMatrixUpdate());

    transformableComponent->Position = {2.0F, 2.0F};
    CHECK(transformableComponent->hasPendingMatrixUpdate());
    test_data.system.rootSceneNode()->componentContainer().updateComponents();
    CHECK_FALSE(transformableComponent->hasPendingMatrixUpdate());

    transformableComponent->Scale = {2.0F, 2.0F};
    CHECK(transformableComponent->hasPendingMatrixUpdate());
    test_data.system.rootSceneNode()->componentContainer().updateComponents();
    CHECK_FALSE(transformableComponent->hasPendingMatrixUpdate());

    transformableComponent->Rotation = {2.0F, 2.0F};
    CHECK(transformableComponent->hasPendingMatrixUpdate());
    test_data.system.rootSceneNode()->componentContainer().updateComponents();
    CHECK_FALSE(transformableComponent->hasPendingMatrixUpdate());
}

TEST_CASE("TransformableComponentAndGlobalTransformationComponent",
          "[TransformationComponent][GlboalTransformationComponent][scene]["
          "component]")
{
    /*
        auto test_data{createComponentForTest<SceneNodesComponent>()};
        auto sceneNodesComponent{test_data.component};
        CHECK(sceneNodesComponent != nullptr);
        auto transformableComponent{
            test_data.system.rootSceneNode()
                ->attachComponent<TransformationComponent>()};
        CHECK(transformableComponent != nullptr);

        auto globalTransformationComponent{
            transformableComponent->getComponent<GlobalTransformationComponent>()};
        CHECK(globalTransformationComponent != nullptr);
        CHECK(test_data.system.rootSceneNode()->components() == 3U);

        auto new1{sceneNodesComponent->createSceneNode("new1")};
        CHECK(new1 != nullptr);
        auto new1TransformableComponent{
            new1->attachComponent<TransformationComponent>()};
        CHECK(new1TransformableComponent != nullptr);
        CHECK(new1->components() == 2U);
        auto new1GlobalTransformationComponent{
            new1->attachComponent<GlobalTransformationComponent>()};
        CHECK(new1GlobalTransformationComponent != nullptr);
        CHECK(new1->components() == 2U);

        CHECK(globalTransformationComponent->hasPendingMatrixUpdate());
        CHECK(transformableComponent->hasPendingMatrixUpdate());
        CHECK(new1GlobalTransformationComponent->hasPendingMatrixUpdate());
        CHECK(new1TransformableComponent->hasPendingMatrixUpdate());
        test_data.system.rootSceneNode()->updateComponents();
        CHECK_FALSE(globalTransformationComponent->hasPendingMatrixUpdate());
        CHECK_FALSE(transformableComponent->hasPendingMatrixUpdate());
        CHECK_FALSE(new1GlobalTransformationComponent->hasPendingMatrixUpdate());
        CHECK_FALSE(new1TransformableComponent->hasPendingMatrixUpdate());
    */
}
