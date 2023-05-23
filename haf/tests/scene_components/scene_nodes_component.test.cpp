#include "catch.hpp"

#include <haf/include/core/types.hpp>
#include <haf/include/scene_components/scene_nodes_component.hpp>

#include "system_test_utils.hpp"
#include "component_test_utils.hpp"

using namespace haf;
using namespace haf::test;
using namespace haf::scene;
using namespace haf::core;
using namespace haf::component;

TEST_CASE("SceneNodesComponent::default_state",
          "[SceneNodesComponent][scene][component]")
{
    auto test_data{createComponentForTest<SceneNodesComponent>()};
    CHECK(test_data.component->empty());
    CHECK(test_data.component->size() == 0U);
}

TEST_CASE("SceneNodesComponent::add_one_and_remove_it",
          "[SceneNodesComponent][scene][component][SceneNodesComponent]")
{
    auto test_data{createComponentForTest<SceneNodesComponent>()};
    core::sptr<SceneNodesComponent> sceneNodesComponent{test_data.component};
    CHECK(sceneNodesComponent->empty());
    CHECK(sceneNodesComponent->size() == 0U);

    auto sceneNode{sceneNodesComponent->createSceneNode("TestSceneNode0")};
    CHECK(sceneNode != nullptr);
    CHECK(sceneNode->name() == "TestSceneNode0");

    bool result{sceneNodesComponent->removeSceneNode("TestSceneNode")};
    CHECK_FALSE(result);

    result = sceneNodesComponent->removeSceneNode(sceneNode);
    CHECK(result);

    CHECK(sceneNodesComponent->empty());
    CHECK(sceneNodesComponent->size() == 0U);
}

TEST_CASE("SceneNodesComponent::add_one_and_remove_it_by_name",
          "[SceneNodesComponent][scene][component]")
{
    auto test_data{createComponentForTest<SceneNodesComponent>()};
    auto sceneNodesComponent{test_data.component};
    CHECK(sceneNodesComponent->empty());
    CHECK(sceneNodesComponent->size() == 0U);

    auto sceneNode{sceneNodesComponent->createSceneNode("TestSceneNode0")};
    CHECK(sceneNode != nullptr);
    CHECK(sceneNode->name() == "TestSceneNode0");

    bool result{sceneNodesComponent->removeSceneNode("TestSceneNode")};
    CHECK_FALSE(result);

    result = sceneNodesComponent->removeSceneNode("TestSceneNode0");
    CHECK(result);

    CHECK(sceneNodesComponent->empty());
    CHECK(sceneNodesComponent->size() == 0U);
}

TEST_CASE("SceneNodesComponent::getByIndex",
          "[SceneNodesComponent][scene][component]")
{
    auto test_data{createComponentForTest<SceneNodesComponent>()};
    auto sceneNodesComponent{test_data.component};

    SceneNodeSPtr sceneNodes[3];
    sceneNodes[0] = sceneNodesComponent->createSceneNode("TestSceneNode0");
    sceneNodes[1] = sceneNodesComponent->createSceneNode("TestSceneNode1");
    sceneNodes[2] = sceneNodesComponent->createSceneNode("TestSceneNode2");

    CHECK(sceneNodesComponent->getByIndex(0U)->name() == "TestSceneNode0");
    CHECK(sceneNodesComponent->getByIndex(1U)->name() == "TestSceneNode1");
    CHECK(sceneNodesComponent->getByIndex(2U)->name() == "TestSceneNode2");
    CHECK(sceneNodesComponent->getByIndex(3U) == nullptr);
}

static core::str lastCreatedName;
static core::str lastRemovedName;

void sceneNodeAdded(const SceneNodeSPtr& node)
{
    lastCreatedName = node->name();
}

void sceneNodeRemoved(const SceneNodeSPtr& node)
{
    lastRemovedName = node->name();
}

TEST_CASE("SceneNodesComponent::removeByIndex",
          "[SceneNodesComponent][scene][component]")
{
    auto test_data{createComponentForTest<SceneNodesComponent>()};
    auto sceneNodesComponent{test_data.component};

    sceneNodesComponent->onNodeAdded.connect(sceneNodeAdded);
    sceneNodesComponent->onNodeRemoved.connect(sceneNodeRemoved);

    SceneNodeSPtr sceneNodes[3];
    sceneNodes[0] = sceneNodesComponent->createSceneNode("TestSceneNode0");
    CHECK(lastCreatedName == "TestSceneNode0");
    sceneNodes[1] = sceneNodesComponent->createSceneNode("TestSceneNode1");
    CHECK(lastCreatedName == "TestSceneNode1");
    sceneNodes[2] = sceneNodesComponent->createSceneNode("TestSceneNode2");
    CHECK(lastCreatedName == "TestSceneNode2");
    CHECK(sceneNodesComponent->size() == 3U);

    CHECK(sceneNodesComponent->removeSceneNode(0U));
    CHECK(sceneNodesComponent->getByIndex(0U)->name() == "TestSceneNode1");
    CHECK(lastRemovedName == "TestSceneNode0");
    CHECK(sceneNodesComponent->size() == 2U);
    CHECK(sceneNodesComponent->removeSceneNode(1U));
    CHECK(lastRemovedName == "TestSceneNode2");
    CHECK(sceneNodesComponent->getByIndex(0U)->name() == "TestSceneNode1");
    CHECK(sceneNodesComponent->size() == 1U);
    CHECK_FALSE(sceneNodesComponent->removeSceneNode(1U));
    CHECK(sceneNodesComponent->removeSceneNode(0U));
    CHECK(lastRemovedName == "TestSceneNode1");
    CHECK(sceneNodesComponent->size() == 0U);
    CHECK(sceneNodesComponent->empty());
}
namespace
{
struct TestComponent : public ComponentBase<"TestComponent">
{
    int data_{0};

private:
    void update() override { ++data_; }
};
}  // namespace

TEST_CASE("SceneNodesComponent::createSceneNodeWithComponent",
          "[SceneNodesComponent][scene][component]")
{
    auto test_data{createComponentForTest<SceneNodesComponent>()};
    auto sceneNodesComponent{test_data.component};
    CHECK(sceneNodesComponent->empty());
    CHECK(sceneNodesComponent->size() == 0U);

    {
        core::sptr<TestComponent> testComponent{
            sceneNodesComponent->createSceneNodeWithComponent<TestComponent>(
                "TestSceneNode")};
        CHECK(testComponent == nullptr);
    }

    test_data.system.registerComponent<TestComponent>();

    core::sptr<TestComponent> testComponent{
        sceneNodesComponent->createSceneNodeWithComponent<TestComponent>(
            "TestSceneNode")};
    CHECK(testComponent != nullptr);
}

TEST_CASE("SceneNodesComponent::forEach",
          "[SceneNodesComponent][scene][component]")
{
    auto test_data{createComponentForTest<SceneNodesComponent>()};
    auto sceneNodesComponent{test_data.component};

    SceneNodeSPtr sceneNodes[3];
    sceneNodes[0] = sceneNodesComponent->createSceneNode("TestSceneNode0");
    sceneNodes[1] = sceneNodesComponent->createSceneNode("TestSceneNode1");
    sceneNodes[2] = sceneNodesComponent->createSceneNode("TestSceneNode2");

    sceneNodesComponent->forEach([](const auto node) { node->Visible = true; });
    CHECK(sceneNodesComponent->getByIndex(0U)->Visible() == true);
    CHECK(sceneNodesComponent->getByIndex(1U)->Visible() == true);
    CHECK(sceneNodesComponent->getByIndex(2U)->Visible() == true);

    sceneNodesComponent->forEach(
        [](const auto node) { node->Visible = false; });
    CHECK(sceneNodesComponent->getByIndex(0U)->Visible() == false);
    CHECK(sceneNodesComponent->getByIndex(1U)->Visible() == false);
    CHECK(sceneNodesComponent->getByIndex(2U)->Visible() == false);
}