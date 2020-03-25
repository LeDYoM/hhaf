#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <lib/scene/include/scene.hpp>
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/scenenodefactory.hpp>

#include <typeinfo>

using namespace lib;
using namespace lib::scene;

class SceneTypeBasic : public Scene
{
public:
    SceneTypeBasic() : Scene{mtps::str("SceneTypeBasic")} {}

    static mtps::uptr<Scene> createScene()
    {
        return mtps::muptr<SceneTypeBasic>();
    }
};

class SceneTypeWithStaticTypeName : public Scene
{
public:
    static constexpr char StaticTypeName[] = "StaticTypeName";

    SceneTypeWithStaticTypeName() : Scene{mtps::str(SceneTypeWithStaticTypeName::StaticTypeName)} {}

    static mtps::uptr<Scene> createScene()
    {
        return mtps::muptr<SceneTypeWithStaticTypeName>();
    }
};

class SceneTypeWithStaticCreateScene : public Scene
{
public:
    SceneTypeWithStaticCreateScene() : Scene{"SceneTypeWithStaticCreateScene"} {}

    static mtps::uptr<Scene> create()
    {
        return mtps::muptr<SceneTypeWithStaticCreateScene>();
    }
};

class SceneTypeWithStaticTypeNameAndStaticCreateScene : public Scene
{
public:
    static constexpr char StaticTypeName[] = "SceneTypeWithStaticTypeNameAndStaticCreateScene";

    SceneTypeWithStaticTypeNameAndStaticCreateScene() : Scene{"SceneTypeWithStaticTypeNameAndStaticCreateScene"} {}

    static mtps::uptr<Scene> create()
    {
        return mtps::muptr<SceneTypeWithStaticTypeNameAndStaticCreateScene>();
    }
};

TEST_CASE("lib::scene::SceneNodeFactory", "[lib][SceneNodeFactory]")
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
            CHECK(scene_node_factory.registerSceneNodeType<SceneTypeWithStaticCreateScene>(mtps::str("SceneTypeWithStaticCreateScene")));
            CHECK(scene_node_factory.registerSceneNodeType<SceneTypeWithStaticTypeNameAndStaticCreateScene>());

            CHECK_FALSE(scene_node_factory.registerSceneNodeType<SceneTypeWithStaticTypeName>(SceneTypeWithStaticTypeName::createScene));            
            CHECK_FALSE(scene_node_factory.registerSceneNodeType<SceneTypeWithStaticCreateScene>(mtps::str("SceneTypeWithStaticCreateScene")));
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
