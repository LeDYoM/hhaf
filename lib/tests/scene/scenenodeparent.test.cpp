#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/scene.hpp>

class TestScene : public lib::scene::Scene
{
    using Scene::Scene;
};

class UnusedScene : public lib::scene::Scene
{
    using Scene::Scene;
};

class TestSceneNode : public lib::scene::SceneNode
{
    using SceneNode::SceneNode;
};

TEST_CASE("SceneNodeParent::SceneNodeParent", "[SceneNode][SceneNodeParent]")
{
    using namespace lib;
    using namespace lib::scene;

    auto test_scene = msptr<TestScene>("TestScene");
    auto scene_node_test(test_scene->createSceneNode<TestSceneNode>("TestSceneNode_test"));
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
        CHECK(scene_node->parentAs<SceneNode>()->snCast<TestSceneNode>() == scene_node_test.get());
    }

    SECTION("Get Parent Scene")
    {
        CHECK(test_scene->parentScene() == test_scene.get());
        CHECK(scene_node_test->parentScene() == test_scene.get());
        CHECK(scene_node->parentScene() == test_scene.get());
    }

    SECTION("Get Parent Scene As")
    {
        CHECK(test_scene->parentSceneAs<TestScene>() == test_scene.get());
        CHECK(scene_node_test->parentSceneAs<TestScene>() == test_scene.get());
        CHECK(scene_node->parentSceneAs<TestScene>() == test_scene.get());
        CHECK(scene_node_test->parentSceneAs<Scene>() == test_scene.get());
        CHECK(scene_node->parentSceneAs<Scene>() == test_scene.get());
        CHECK(scene_node->parentSceneAs<Scene>()->snCast<TestScene>() == test_scene.get());
        CHECK(scene_node_test->parentSceneAs<TestSceneNode>() == nullptr);
        CHECK(scene_node->parentSceneAs<TestSceneNode>() == nullptr);
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
