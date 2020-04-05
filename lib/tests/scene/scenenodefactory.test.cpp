#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <lib/scene/include/scene.hpp>
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/scenenodefactory.hpp>

#include <typeinfo>

using namespace mtps;
using namespace haf;
using namespace haf::scene;

class SceneTypeBasic : public Scene
{
public:
    SceneTypeBasic() : Scene{str("SceneTypeBasic")} {}

    static uptr<Scene> createScene()
    {
        return muptr<SceneTypeBasic>();
    }
};

class SceneTypeWithStaticTypeName : public Scene
{
public:
    static constexpr char StaticTypeName[] = "StaticTypeName";

    SceneTypeWithStaticTypeName() : Scene{str(SceneTypeWithStaticTypeName::StaticTypeName)} {}

    static uptr<Scene> createScene()
    {
        return muptr<SceneTypeWithStaticTypeName>();
    }
};

class SceneTypeWithStaticCreateScene : public Scene
{
public:
    SceneTypeWithStaticCreateScene() : Scene{"SceneTypeWithStaticCreateScene"} {}

    static uptr<Scene> create()
    {
        return muptr<SceneTypeWithStaticCreateScene>();
    }
};

class SceneTypeWithStaticTypeNameAndStaticCreateScene : public Scene
{
public:
    static constexpr char StaticTypeName[] = "SceneTypeWithStaticTypeNameAndStaticCreateScene";

    SceneTypeWithStaticTypeNameAndStaticCreateScene() : Scene{"SceneTypeWithStaticTypeNameAndStaticCreateScene"} {}

    static uptr<Scene> create()
    {
        return muptr<SceneTypeWithStaticTypeNameAndStaticCreateScene>();
    }
};

TEST_CASE("haf::scene::SceneNodeFactory", "[lib][SceneNodeFactory]")
{
    SceneNodeFactory scene_node_factory;

    SECTION("Basic insertion")
    {
        CHECK(scene_node_factory.registerSceneNodeType("SceneTypeBasic", SceneTypeBasic::createScene));
        // Insertion of the same element is false
        CHECK_FALSE(scene_node_factory.registerSceneNodeType("SceneTypeBasic", SceneTypeBasic::createScene));

        SECTION("Inserting overloads")
        {
            CHECK(scene_node_factory.registerSceneNodeType<SceneTypeWithStaticTypeName>(SceneTypeWithStaticTypeName::createScene));            
            CHECK(scene_node_factory.registerSceneNodeType<SceneTypeWithStaticCreateScene>(str("SceneTypeWithStaticCreateScene")));
            CHECK(scene_node_factory.registerSceneNodeType<SceneTypeWithStaticTypeNameAndStaticCreateScene>());

            CHECK_FALSE(scene_node_factory.registerSceneNodeType<SceneTypeWithStaticTypeName>(SceneTypeWithStaticTypeName::createScene));            
            CHECK_FALSE(scene_node_factory.registerSceneNodeType<SceneTypeWithStaticCreateScene>(str("SceneTypeWithStaticCreateScene")));
            CHECK_FALSE(scene_node_factory.registerSceneNodeType<SceneTypeWithStaticTypeNameAndStaticCreateScene>());

            SECTION("Check existence")
            {
                auto scene_type_basic = scene_node_factory.create("SceneTypeBasic");
                CHECK(scene_type_basic != nullptr);
                CHECK(typeid(*scene_type_basic) == typeid(SceneTypeBasic));

                auto scene_type_complete = scene_node_factory.create<SceneTypeWithStaticTypeName>();
                CHECK(scene_type_complete != nullptr);
                CHECK(typeid(*scene_type_complete) == typeid(SceneTypeWithStaticTypeName));
            }
        }
    }
}
