#include "catch.hpp"

#include <haf/include/core/types.hpp>
#include <haf/include/scene_components/visibility_selector_component.hpp>

#include "system_test_utils.hpp"
#include "component_test_utils.hpp"

using namespace haf;
using namespace haf::test;
using namespace haf::scene;
using namespace haf::core;
using namespace haf::component;

TEST_CASE(
    "VisibilitySelectorComponent::VisibilitySelectorComponent",
    "[VisibilitySelectorComponent][scene][component][SceneNodesComponent]")
{
    auto test_data{createComponentForTest<VisibilitySelectorComponent>()};
    auto visibilitySelectorComponent{test_data.component};
    CHECK(visibilitySelectorComponent != nullptr);
/*    auto sceneNodesComponent{
        visibilitySelectorComponent->getComponent<SceneNodesComponent>()};
    CHECK(sceneNodesComponent != nullptr);

    sceneNodesComponent->createSceneNode("TestSceneNode0");
    sceneNodesComponent->createSceneNode("TestSceneNode1");
    sceneNodesComponent->createSceneNode("TestSceneNode2");

    visibilitySelectorComponent->updateComponent();
    CHECK(sceneNodesComponent->getByIndex(0U)->Visible() == true);
    CHECK(sceneNodesComponent->getByIndex(1U)->Visible() == false);
    CHECK(sceneNodesComponent->getByIndex(2U)->Visible() == false);

    visibilitySelectorComponent->visible_index = 1U;
    visibilitySelectorComponent->updateComponent();
    CHECK(sceneNodesComponent->getByIndex(0U)->Visible() == false);
    CHECK(sceneNodesComponent->getByIndex(1U)->Visible() == true);
    CHECK(sceneNodesComponent->getByIndex(2U)->Visible() == false);

    visibilitySelectorComponent->visible_index = 3U;
    visibilitySelectorComponent->updateComponent();
    CHECK(sceneNodesComponent->getByIndex(0U)->Visible() == false);
    CHECK(sceneNodesComponent->getByIndex(1U)->Visible() == false);
    CHECK(sceneNodesComponent->getByIndex(2U)->Visible() == false);

    sceneNodesComponent->createSceneNode("TestSceneNode3");
    visibilitySelectorComponent->updateComponent();
    CHECK(sceneNodesComponent->getByIndex(0U)->Visible() == false);
    CHECK(sceneNodesComponent->getByIndex(1U)->Visible() == false);
    CHECK(sceneNodesComponent->getByIndex(2U)->Visible() == false);
    CHECK(sceneNodesComponent->getByIndex(3U)->Visible() == true);
*/
}
