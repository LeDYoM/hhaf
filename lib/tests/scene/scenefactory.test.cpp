#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/scenefactory.hpp>

#include <typeinfo>

using namespace lib;
using namespace lib::scene;

class SceneTypeBasic : public Scene
{
public:
    SceneTypeBasic() : Scene{str("SceneTypeBasic")} {}

    static uptr<Scene> create()
    {
        return muptr<SceneTypeBasic>();
    }
};

class SceneTypeWithStaticTypeName : public Scene
{
public:
    static constexpr char StaticTypeName[] = "StaticTypeName";

    SceneTypeWithStaticTypeName() : Scene{str(SceneTypeWithStaticTypeName::StaticTypeName)} {}

    static uptr<Scene> create()
    {
        return muptr<SceneTypeWithStaticTypeName>();
    }
};

class SceneTypeWithStaticCreateScene : public Scene
{
public:
    SceneTypeWithStaticCreateScene() : Scene{"SceneTypeWithStaticCreateScene"} {}

    static uptr<Scene> createScene()
    {
        return muptr<SceneTypeWithStaticCreateScene>();
    }
};

class SceneTypeWithStaticTypeNameAndStaticCreateScene : public Scene
{
public:
    static constexpr char StaticTypeName[] = "SceneTypeWithStaticTypeNameAndStaticCreateScene";

    SceneTypeWithStaticTypeNameAndStaticCreateScene() : Scene{"SceneTypeWithStaticTypeNameAndStaticCreateScene"} {}

    static uptr<Scene> createScene()
    {
        return muptr<SceneTypeWithStaticTypeNameAndStaticCreateScene>();
    }
};

TEST_CASE("lib::scene::SceneFactory", "[lib][SceneFactory]")
{
    SceneFactory scene_factory;

    SECTION("Basic insertion")
    {
        CHECK(scene_factory.registerSceneType("SceneTypeBasic", SceneTypeBasic::create));
        // Insertion of the same element is false
        CHECK_FALSE(scene_factory.registerSceneType("SceneTypeBasic", SceneTypeBasic::create));

        SECTION("Inserting overloads")
        {
            CHECK(scene_factory.registerSceneType<SceneTypeWithStaticTypeName>(SceneTypeWithStaticTypeName::create));            
            CHECK(scene_factory.registerSceneType<SceneTypeWithStaticCreateScene>(str("SceneTypeWithStaticCreateScene")));
            CHECK(scene_factory.registerSceneType<SceneTypeWithStaticTypeNameAndStaticCreateScene>());

            CHECK_FALSE(scene_factory.registerSceneType<SceneTypeWithStaticTypeName>(SceneTypeWithStaticTypeName::create));            
            CHECK_FALSE(scene_factory.registerSceneType<SceneTypeWithStaticCreateScene>(str("SceneTypeWithStaticCreateScene")));
            CHECK_FALSE(scene_factory.registerSceneType<SceneTypeWithStaticTypeNameAndStaticCreateScene>());

            SECTION("Check existence")
            {
                auto scene_type_basic = scene_factory.create("SceneTypeBasic");
                CHECK(scene_type_basic != nullptr);
                CHECK(typeid(*scene_type_basic) == typeid(SceneTypeBasic));

                auto scene_type_complete = scene_factory.create<SceneTypeWithStaticTypeName>();
                CHECK(scene_type_complete != nullptr);
                CHECK(typeid(*scene_type_complete) == typeid(SceneTypeWithStaticTypeName));
            }
        }
    }
}
