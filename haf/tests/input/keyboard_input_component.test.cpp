#include "catch.hpp"

#include <haf/include/core/types.hpp>
#include <haf/include/input/keyboard_input_component.hpp>
#include <haf/include/scene_components/scene_nodes_component.hpp>

#include "system_test_utils.hpp"
#include "component_test_utils.hpp"

using namespace haf;
using namespace haf::math;
using namespace haf::test;
using namespace haf::scene;
using namespace haf::core;
using namespace haf::component;
using namespace haf::input;

TEST_CASE("KeyboardInputComponent::KeyboardInputComponent",
          "[KeyboardInputComponent][input][component]")
{
    auto test_data{createComponentForTest<KeyboardInputComponent>()};
    auto keyboardInputComponent{test_data.component};
    CHECK(keyboardInputComponent != nullptr);
}

TEST_CASE("KeyboardInputComponent::KeyboardInputComponent::KeyPressed",
          "[KeyboardInputComponent][input][component]")
{
    auto test_data{createComponentForTest<KeyboardInputComponent>()};
    auto keyboardInputComponent{test_data.component};
    CHECK(keyboardInputComponent != nullptr);
    static Key k;
    keyboardInputComponent->KeyPressed += [](const Key& key)
    {
        k = key;
    };
    // TODO: Simulate?
}

/*
TEST_CASE("KeyboardInputComponent::DefaultValues",
          "[KeyboardInputComponent][input][component]")
{
    auto test_data{createComponentForTest<GlobalTransformationComponent>()};
    auto globalTransformationComponent{test_data.component};
    CHECK(globalTransformationComponent != nullptr);

    CHECK(globalTransformationComponent->hasPendingMatrixUpdate());
    test_data.system.rootSceneNode()->updateComponents();
    CHECK_FALSE(globalTransformationComponent->hasPendingMatrixUpdate());
}

TEST_CASE("KeyboardInputComponent::updateFromParent",
          "[KeyboardInputComponent][input][component]")
{
    auto test_data{createComponentForTest<SceneNodesComponent>()};
    auto sceneNodesComponent{test_data.component};
    CHECK(sceneNodesComponent != nullptr);
    auto globalTransformationComponent{
        test_data.system.rootSceneNode()
            ->getOrCreateComponent<GlobalTransformationComponent>()};
    CHECK(globalTransformationComponent != nullptr);

    CHECK(globalTransformationComponent->hasPendingMatrixUpdate());
    test_data.system.rootSceneNode()->updateComponents();
    CHECK_FALSE(globalTransformationComponent->hasPendingMatrixUpdate());

    auto new1{sceneNodesComponent->createSceneNode("New1")};
    CHECK(new1 != nullptr);
    auto new1GlobalTransformationComponent{
        new1->getOrCreateComponent<GlobalTransformationComponent>()};
    CHECK(new1GlobalTransformationComponent != nullptr);
    CHECK(new1GlobalTransformationComponent->hasPendingMatrixUpdate());
    new1->updateComponents();
    CHECK_FALSE(new1GlobalTransformationComponent->hasPendingMatrixUpdate());

    test_data.system.rootSceneNode()->updateComponents();
    CHECK_FALSE(globalTransformationComponent->hasPendingMatrixUpdate());
    CHECK_FALSE(new1GlobalTransformationComponent->hasPendingMatrixUpdate());

    Matrix4x4 matrix{Matrix4x4::Identity};
    globalTransformationComponent->localTransformationChanged(&matrix);
    CHECK(globalTransformationComponent->hasPendingMatrixUpdate());

    test_data.system.rootSceneNode()->updateComponents();
    CHECK_FALSE(new1GlobalTransformationComponent->hasPendingMatrixUpdate());
}
*/