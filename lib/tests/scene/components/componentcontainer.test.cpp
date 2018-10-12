#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/components/componentcontainer.hpp>
#include <lib/scene/components/icomponent.hpp>

using namespace lib;
using namespace lib::scene;

static auto unitTestScene()
{
    static auto uts(lib::msptr<lib::scene::Scene>("unitTest"));
    return uts;
}

class TestComponent : public IComponent
{

};

TEST_CASE("lib::scene::ComponentContainer::ComponentContainer", "[ComponentContainer][constructor]")
{
    sptr<ComponentContainer> componentContainerNoParent(msptr<ComponentContainer>());
    CHECK(componentContainerNoParent->componentOfType)

    auto node_test(unitTestScene()->createSceneNode("SceneNode_test"));
    CHECK(unitTestScene()->sceneNodesSize() == 1);
    CHECK(unitTestScene()->renderNodesSize() == 0);
    CHECK(node_test->sceneNodesSize() == 0);
    CHECK(node_test->renderNodesSize() == 0);
}
