#include "catch.hpp"

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/vector2d.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene_nodes/transformable_scene_node.hpp>
#include <haf/include/scene/scene_nodes.hpp>
#include <haf/include/scene/scene.hpp>

using namespace htps;
namespace
{
auto unitTestScene()
{
    return msptr<haf::scene::Scene>("unitTest");
}
}  // namespace

class TestSceneNode : public haf::scene::SceneNode
{
    using haf::scene::SceneNode::SceneNode;
};

class TestTransformableSceneNode : public haf::scene::TransformableSceneNode
{
    using haf::scene::TransformableSceneNode::TransformableSceneNode;
};

TEST_CASE("Scenenodes::for_each", "[SceneNode][SceneNodes]")
{
    using namespace haf;
    using namespace haf::scene;

    constexpr size_type kNumSceneNodes{10U};
    auto testScene(unitTestScene());

    // Create 10 scene nodes
    for (size_type index{0U}; index < kNumSceneNodes; ++index)
    {
        str name{make_str("SceneNode_test_", index)};
        auto node_test(testScene->createSceneNode(name));
    }
    CHECK(testScene->sceneNodes().size() == kNumSceneNodes);

    size_type numCheck{0U};

    testScene->for_each_sceneNode(
        [&numCheck](sptr<SceneNode> const& childNode) {
            childNode->prop<Visible>().set(false);
            ++numCheck;
        });

    CHECK(numCheck == kNumSceneNodes);
    numCheck = 0U;

    for (auto const childNode : testScene->sceneNodes())
    {
        CHECK(childNode->prop<Visible>().get() == false);
        ++numCheck;
    }

    CHECK(numCheck == kNumSceneNodes);
    numCheck = 0U;

    // Create more scene nodes with different static type
    for (size_type index{0U}; index < kNumSceneNodes; ++index)
    {
        str name{make_str("SceneNode_test_", index)};
        auto node_test(testScene->createSceneNode<TestSceneNode>(name));
    }

    CHECK(testScene->sceneNodes().size() == kNumSceneNodes * 2U);

    testScene->for_each_sceneNode(
        [&numCheck](sptr<SceneNode> const& childNode) {
            childNode->prop<Visible>().set(false);
            ++numCheck;
        });

    CHECK(numCheck == kNumSceneNodes * 2U);
    numCheck = 0U;

    for (auto const childNode : testScene->sceneNodes())
    {
        CHECK(childNode->prop<Visible>().get() == false);
        ++numCheck;
    }

    CHECK(numCheck == kNumSceneNodes * 2U);
    numCheck = 0U;

    testScene->for_each_sceneNode_as<TestSceneNode>(
        [&numCheck](sptr<TestSceneNode> const& childNode) {
            childNode->prop<Visible>().set(true);
            ++numCheck;
        });

    CHECK(numCheck == kNumSceneNodes);
    numCheck = 0U;
}

TEST_CASE("Scenenodes::for_each const", "[SceneNode][SceneNodes]")
{
    using namespace haf;
    using namespace haf::scene;

    constexpr size_type kNumSceneNodes{10U};
    auto testScene(unitTestScene());
    sptr<Scene const> testScene_ = testScene;

    // Create 10 scene nodes
    for (size_type index{0U}; index < kNumSceneNodes; ++index)
    {
        str name{make_str("SceneNode_test_", index)};
        auto node_test(testScene->createSceneNode(name));
    }
    CHECK(testScene_->sceneNodes().size() == kNumSceneNodes);

    size_type numCheck{0U};

    testScene_->for_each_sceneNode(
        [&numCheck](sptr<SceneNode const> const& childNode) {
            CHECK(childNode->prop<Visible>().get() == true);
            ++numCheck;
        });

    CHECK(numCheck == kNumSceneNodes);
    numCheck = 0U;

    // Create more scene nodes with different static type
    for (size_type index{0U}; index < kNumSceneNodes; ++index)
    {
        str name{make_str("SceneNode_test_", index)};
        auto node_test(testScene->createSceneNode<TestSceneNode>(name));
    }

    CHECK(testScene_->sceneNodes().size() == kNumSceneNodes * 2U);

    testScene_->for_each_sceneNode(
        [&numCheck](sptr<SceneNode const> const& childNode) {
            CHECK(childNode->prop<Visible>().get() == true);
            ++numCheck;
        });

    CHECK(numCheck == kNumSceneNodes * 2U);
    numCheck = 0U;

    testScene_->for_each_sceneNode_as<TestSceneNode>(
        [&numCheck](sptr<TestSceneNode const> const& childNode) {
            CHECK(childNode->prop<Visible>().get() == true);
            ++numCheck;
        });

    CHECK(numCheck == kNumSceneNodes);
    numCheck = 0U;
}

TEST_CASE("Scenenodes::set_property_for_each_sceneNode",
          "[SceneNode][SceneNodes]")
{
    using namespace haf;
    using namespace haf::scene;

    constexpr size_type kNumSceneNodes{10U};
    auto testScene(unitTestScene());

    // Create 10 scene nodes
    for (size_type index{0U}; index < kNumSceneNodes; ++index)
    {
        str name{make_str("SceneNode_test_", index)};
        auto node_test(testScene->createSceneNode(name));
    }
    CHECK(testScene->sceneNodes().size() == kNumSceneNodes);

    //    testScene->set_property_for_each_sceneNode<Visible>(true);

    size_type numCheck{0U};

    for (auto const childNode : testScene->sceneNodes())
    {
        CHECK(childNode->prop<Visible>().get() == true);
        ++numCheck;
    }

    CHECK(numCheck == kNumSceneNodes);
    numCheck = 0U;

    // Create more scene nodes with different static type
    for (size_type index{0U}; index < kNumSceneNodes; ++index)
    {
        str name{make_str("SceneNode_test_", index)};
        auto node_test(testScene->createSceneNode<TestSceneNode>(name));
    }

    //    testScene->set_property_for_each_sceneNode_as<TestSceneNode, Visible>(
    //        true);

    for (auto const childNode : testScene->sceneNodes())
    {
        if (auto node = std::dynamic_pointer_cast<TestSceneNode>(childNode))
        {
            CHECK(childNode->prop<Visible>().get() == true);
            ++numCheck;
        }
    }

    CHECK(numCheck == kNumSceneNodes);
}

TEST_CASE("Scenenodes::getByName", "[SceneNode][SceneNodes]")
{
    using namespace haf;
    using namespace haf::scene;

    constexpr size_type kNumSceneNodes{10U};
    auto testScene(unitTestScene());
    sptr<SceneNode> node_test;

    // Create 10 scene nodes
    for (size_type index{0U}; index < kNumSceneNodes; ++index)
    {
        str name{make_str("SceneNode_test_", index)};
        if (index == 0U)
        {
            node_test = testScene->createSceneNode(name);
        }
        else
        {
            testScene->createSceneNode(name);
        }
    }

    CHECK(testScene->sceneNodes().size() == kNumSceneNodes);

    auto result = testScene->getByName("SceneNode_test_0");
    CHECK(result == node_test);
    result = testScene->getByName("SceneNode_test");
    CHECK(result == nullptr);
}

TEST_CASE("Scenenodes::removeSceneNode", "[SceneNode][SceneNodes]")
{
    using namespace haf;
    using namespace haf::scene;

    constexpr size_type kNumSceneNodes{10U};
    auto testScene(unitTestScene());
    sptr<SceneNode> node_test;

    // Create 10 scene nodes
    for (size_type index{0U}; index < kNumSceneNodes; ++index)
    {
        str name{make_str("SceneNode_test_", index)};
        if (index == 0U)
        {
            node_test = testScene->createSceneNode(name);
        }
        else
        {
            testScene->createSceneNode(name);
        }
    }

    CHECK(testScene->sceneNodes().size() == kNumSceneNodes);

    auto result = testScene->removeSceneNode(node_test);
    CHECK(result == true);
    result = testScene->removeSceneNode(node_test);
    CHECK(result == false);
    CHECK(testScene->sceneNodes().size() == kNumSceneNodes - 1U);
}

TEST_CASE("Scenenodes::removeSceneNodeNyName", "[SceneNode][SceneNodes]")
{
    using namespace haf;
    using namespace haf::scene;

    constexpr size_type kNumSceneNodes{10U};
    auto testScene(unitTestScene());
    sptr<SceneNode> node_test;

    // Create 10 scene nodes
    for (size_type index{0U}; index < kNumSceneNodes; ++index)
    {
        str name{make_str("SceneNode_test_", index)};
        if (index == 0U)
        {
            node_test = testScene->createSceneNode(name);
        }
        else
        {
            testScene->createSceneNode(name);
        }
    }

    CHECK(testScene->sceneNodes().size() == kNumSceneNodes);

    auto result = testScene->removeSceneNode("SceneNode_test_0");
    CHECK(result == true);
    result = testScene->removeSceneNode("SceneNode_test_0");
    CHECK(result == false);
    CHECK(testScene->sceneNodes().size() == kNumSceneNodes - 1U);
}

TEST_CASE("Scenenodes::removeSceneNodeByNode", "[SceneNode][SceneNodes]")
{
    using namespace haf;
    using namespace haf::scene;

    constexpr size_type kNumSceneNodes{10U};
    auto testScene(unitTestScene());
    sptr<SceneNode> node_test;

    // Create 10 scene nodes
    for (size_type index{0U}; index < kNumSceneNodes; ++index)
    {
        str name{make_str("SceneNode_test_", index)};
        if (index == 0U)
        {
            node_test = testScene->createSceneNode(name);
        }
        else
        {
            testScene->createSceneNode(name);
        }
    }

    CHECK(testScene->sceneNodes().size() == kNumSceneNodes);
    testScene->clearSceneNodes();
    CHECK(testScene->sceneNodes().size() == 0U);
}

TEST_CASE("Scenenodes::for_each_as", "[SceneNode]")
{
    using namespace haf;
    using namespace haf::scene;

    constexpr size_type kNumSceneNodes{10U};
    auto testScene(unitTestScene());

    // Create 10 scene nodes
    for (size_type index{0U}; index < kNumSceneNodes; ++index)
    {
        str name{make_str("SceneNode_test_", index)};
        auto node_test(
            testScene->createSceneNode<TransformableSceneNode>(name));
    }
    CHECK(testScene->sceneNodes().size() == kNumSceneNodes);

    size_type numCheck{0U};

    testScene->for_each_sceneNode_as<TransformableSceneNode>(
        [&numCheck](sptr<TransformableSceneNode> const& childNode) {
            childNode->prop<Position>().set({1.0F, 2.0F});
            ++numCheck;
        });

    CHECK(numCheck == kNumSceneNodes);
    numCheck = 0U;

    for (auto const childNode : testScene->sceneNodes())
    {
        CHECK(std::dynamic_pointer_cast<TransformableSceneNode>(childNode)
                  ->prop<Position>()
                  .get() == vector2df{1.0F, 2.0F});
        ++numCheck;
    }

    CHECK(numCheck == kNumSceneNodes);
    numCheck = 0U;

    // Create more scene nodes with different static type
    for (size_type index{0U}; index < kNumSceneNodes; ++index)
    {
        str name{make_str("SceneNode_test_", index)};
        auto node_test(
            testScene->createSceneNode<TestTransformableSceneNode>(name));
    }

    CHECK(testScene->sceneNodes().size() == kNumSceneNodes * 2U);

    testScene->for_each_sceneNode_as<TransformableSceneNode>(
        [&numCheck](sptr<TransformableSceneNode> const& childNode) {
            childNode->prop<Position>().set({10.0F, 20.0F});
            ++numCheck;
        });

    CHECK(numCheck == kNumSceneNodes * 2U);
    numCheck = 0U;

    for (auto const childNode : testScene->sceneNodes())
    {
        CHECK(std::dynamic_pointer_cast<TransformableSceneNode>(childNode)
                  ->prop<Position>()
                  .get() == vector2df{10.0F, 20.0F});
        ++numCheck;
    }

    CHECK(numCheck == kNumSceneNodes * 2U);
    numCheck = 0U;

    testScene->for_each_sceneNode_as<TestTransformableSceneNode>(
        [&numCheck](sptr<TestTransformableSceneNode> const& childNode) {
            childNode->prop<Position>().set({100.0F, 200.0F});
            ++numCheck;
        });

    CHECK(numCheck == kNumSceneNodes);
    numCheck = 0U;
}

TEST_CASE("Scenenodes::for_each_as const", "[SceneNode][SceneNodes]")
{
    using namespace haf;
    using namespace haf::scene;

    constexpr size_type kNumSceneNodes{10U};
    auto testScene(unitTestScene());
    sptr<Scene const> testScene_ = testScene;

    // Create 10 scene nodes
    for (size_type index{0U}; index < kNumSceneNodes; ++index)
    {
        str name{make_str("SceneNode_test_", index)};
        auto node_test(
            testScene->createSceneNode<TransformableSceneNode>(name));
    }
    CHECK(testScene_->sceneNodes().size() == kNumSceneNodes);

    size_type numCheck{0U};

    testScene_->for_each_sceneNode_as<TransformableSceneNode>(
        [&numCheck](sptr<TransformableSceneNode const> const& childNode) {
            CHECK(childNode->prop<Position>().get() == vector2df{});
            ++numCheck;
        });

    CHECK(numCheck == kNumSceneNodes);
    numCheck = 0U;

    // Create more scene nodes with different static type
    for (size_type index{0U}; index < kNumSceneNodes; ++index)
    {
        str name{make_str("SceneNode_test_", index)};
        auto node_test(
            testScene->createSceneNode<TestTransformableSceneNode>(name));
    }

    CHECK(testScene_->sceneNodes().size() == kNumSceneNodes * 2U);

    testScene_->for_each_sceneNode_as<TransformableSceneNode>(
        [&numCheck](sptr<TransformableSceneNode const> const& childNode) {
            CHECK(childNode->prop<Position>().get() == vector2df{});
            ++numCheck;
        });

    CHECK(numCheck == kNumSceneNodes * 2U);
    numCheck = 0U;

    testScene_->for_each_sceneNode_as<TestTransformableSceneNode>(
        [&numCheck](sptr<TestTransformableSceneNode const> const& childNode) {
            CHECK(childNode->prop<Position>().get() == vector2df{});
            ++numCheck;
        });

    CHECK(numCheck == kNumSceneNodes);
    numCheck = 0U;
}

TEST_CASE("Scenenodes::set_property_for_each_as", "[SceneNode][SceneNodes]")
{
    using namespace haf;
    using namespace haf::scene;

    constexpr size_type kNumSceneNodes{10U};
    auto testScene(unitTestScene());

    // Create 10 scene nodes
    for (size_type index{0U}; index < kNumSceneNodes; ++index)
    {
        str name{make_str("SceneNode_test_", index)};
        auto node_test(
            testScene->createSceneNode<TransformableSceneNode>(name));
    }
    CHECK(testScene->sceneNodes().size() == kNumSceneNodes);

    testScene
        ->set_property_for_each_sceneNode_as<TransformableSceneNode, Position>(
            vector2df{4.5F, 3.5F});

    size_type numCheck{0U};

    for (auto const childNode : testScene->sceneNodes())
    {
        CHECK(std::dynamic_pointer_cast<TransformableSceneNode>(childNode)
                  ->prop<Position>()
                  .get() == vector2df{4.5F, 3.5F});
        ++numCheck;
    }

    CHECK(numCheck == kNumSceneNodes);
    numCheck = 0U;

    // Create more scene nodes with different static type
    for (size_type index{0U}; index < kNumSceneNodes; ++index)
    {
        str name{make_str("SceneNode_test_", index)};
        auto node_test(
            testScene->createSceneNode<TestTransformableSceneNode>(name));
    }

    testScene->set_property_for_each_sceneNode_as<TestTransformableSceneNode,
                                                  Position>(
        vector2df{33.0F, 44.0F});

    for (auto const childNode : testScene->sceneNodes())
    {
        if (auto node = std::dynamic_pointer_cast<TestTransformableSceneNode>(
                childNode))
        {
            CHECK(node->prop<Position>().get() == vector2df{33.0F, 44.0F});
            ++numCheck;
        }
    }

    CHECK(numCheck == kNumSceneNodes);
}

TEST_CASE("Scenenodes::removeSceneNodeByNodeTestNode",
          "[SceneNode][SceneNodes]")
{
    using namespace haf;
    using namespace haf::scene;

    constexpr size_type kNumSceneNodes{10U};
    auto testScene(unitTestScene());
    sptr<TestTransformableSceneNode> node_test;

    // Create 10 scene nodes
    for (size_type index{0U}; index < kNumSceneNodes; ++index)
    {
        str name{make_str("SceneNode_test_", index)};
        if (index == 0U)
        {
            node_test =
                testScene->createSceneNode<TestTransformableSceneNode>(name);
        }
        else
        {
            testScene->createSceneNode<TestTransformableSceneNode>(name);
        }
    }

    CHECK(testScene->sceneNodes().size() == kNumSceneNodes);
    testScene->clearSceneNodes();
    CHECK(testScene->sceneNodes().size() == 0U);
}

template <size_type kNumSceneNodes>
auto createTestTransformableSceneNodes(sptr<haf::scene::Scene> scene)
{
    sptr<TestTransformableSceneNode> node_test;

    // Create 10 scene nodes
    for (size_type index{0U}; index < kNumSceneNodes; ++index)
    {
        auto result{scene->createSceneNode<TestTransformableSceneNode>(
            make_str("SceneNode_test_", index))};
        if (index == 0U)
        {
            node_test = std::move(result);
        }
    }
    return node_test;
}

TEST_CASE("Scenenodes::autoRemove", "[SceneNode][SceneNodes]")
{
    using namespace haf;
    using namespace haf::scene;

    constexpr size_type kNumSceneNodes{10U};
    auto testScene(unitTestScene());
    sptr<TestTransformableSceneNode> node_test{
        createTestTransformableSceneNodes<kNumSceneNodes>(testScene)};

    CHECK(testScene->sceneNodes().size() == kNumSceneNodes);

    // Get the raw pointer
    TestTransformableSceneNode* node_test_raw{node_test.get()};
    CHECK(node_test == testScene->getShared(node_test_raw));
    CHECK(node_test->autoRemove());
    CHECK(testScene->sceneNodes().size() == (kNumSceneNodes - 1U));
}
