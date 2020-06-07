#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <haf/scene/include/scene.hpp>

using namespace mtps;

class TestScene : public haf::scene::Scene
{
    using Scene::Scene;
};

class UnusedScene : public haf::scene::Scene
{
    using Scene::Scene;
};

class TestSceneNode : public haf::scene::SceneNode
{
public:
    using SceneNode::SceneNode;
    virtual ~TestSceneNode() {}
};

TEST_CASE("SceneNodeParent::SceneNodeParent", "[SceneNode][SceneNodeParent]")
{
    using namespace haf;
    using namespace haf::scene;

    auto test_scene = msptr<TestScene>("TestScene");
    auto scene_node_test(
        test_scene->createSceneNode<TestSceneNode>("TestSceneNode_test"));
    auto scene_node(scene_node_test->createSceneNode("TestSceneNode"));

    SECTION("Get Parent")
    {
        CHECK(test_scene->parent() == nullptr);
        CHECK(scene_node_test->parent() == test_scene.get());
        CHECK(scene_node->parent() == scene_node_test.get());
    }

    SECTION("Get ParentAs")
    {
        CHECK(scene_node_test->parentAs<TestScene>() == test_scene.get());
        CHECK(scene_node_test->parentAs<TestSceneNode>() == nullptr);
        CHECK(scene_node->parentAs<TestScene>() == nullptr);
        CHECK(scene_node->parentAs<TestSceneNode>() == scene_node_test.get());
        CHECK(scene_node->parentAs<SceneNode>() == scene_node_test.get());
        CHECK(scene_node->parentAs<SceneNode>()->snCast<TestSceneNode>() ==
              scene_node_test.get());
    }

    SECTION("Ancestor")
    {
        CHECK(scene_node->ancestor<TestSceneNode>() == scene_node_test.get());
        CHECK(scene_node->ancestor<Scene>() == test_scene.get());
        CHECK(scene_node->ancestor<UnusedScene>() == nullptr);
        CHECK(scene_node->ancestor<TestScene>() == test_scene.get());
        CHECK(scene_node->ancestor() == scene_node_test.get());

        CHECK(scene_node_test->ancestor<TestSceneNode>() == nullptr);
        CHECK(scene_node_test->ancestor<Scene>() == test_scene.get());
        CHECK(scene_node_test->ancestor<UnusedScene>() == nullptr);
        CHECK(scene_node_test->ancestor<TestScene>() == test_scene.get());
        CHECK(scene_node_test->ancestor() == test_scene.get());
    }
}
