#include "catch.hpp"

#include <haf/include/core/types.hpp>
#include <haf/include/properties/property_state.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/component/component_container.hpp>
#include <haf/include/component/component_declaration.hpp>
#include <haf/include/component/component_definition.hpp>

#include "system_test_utils.hpp"

using namespace htps;
using namespace haf;
using namespace haf::test;
using namespace haf::scene;
using namespace haf::component;
using namespace haf::prop;

namespace
{
struct TestComponent : public ComponentBootStrap<TestComponent, "Test">
{
    static constexpr const core::str_view StaticTypeName{"TestComponent"};

    int data_{0};

    void onAttached() override { addUpdater({this, &TestComponent::updater}); }

private:
    void updater() { ++data_; }
};

struct TestComponent2 : public ComponentBootStrap<TestComponent2, "Test">
{
    static constexpr const core::str_view StaticTypeName{"TestComponent2"};

    int data_{0};

private:
    //    void update() override { ++data_; }
};

struct TestComponent3 : public ComponentBootStrap<TestComponent3, "Test">
{
    static constexpr const core::str_view StaticTypeName{"TestComponent3"};
    int data_{0};

private:
    //    void update() { ++data_; }
};
}  // namespace

TEST_CASE("ComponentMetadata", "[ComponentContainer][Component]")
{
    bool a = TestComponent::StaticTypeName == core::str_view{"TestComponent"};
    CHECK(a);
    CHECK(TestComponent::StaticTypeName == core::str_view{"TestComponent"});
    CHECK(TestComponent::StaticTypeName == core::str{"TestComponent"});
    TestComponent test_component;
    CHECK(test_component.staticTypeName() == core::str_view{"TestComponent"});
    CHECK(test_component.staticTypeName() == core::str{"TestComponent"});
}

TEST_CASE("haf::scene::ComponentContainer", "[ComponentContainer][constructor]")
{
    auto t_system{createSystemForTest<TestSceneManager>()};
    ComponentContainer& component_container{
        t_system.system.rootSceneNode()->componentContainer()};
    CHECK(t_system.system.registerComponent<TestComponent>());

    SECTION("Add component")
    {
        sptr<TestComponent> component{
            component_container.attachComponent<TestComponent>()};
        CHECK(component != nullptr);

        sptr<TestComponent> component_other{
            component_container.attachComponent<TestComponent>()};
        CHECK(component == component_other);

        SECTION("Update")
        {
            //            component_container.updateComponents();
            //            CHECK(component->data_ == 1);
            /*
                        SECTION("Try Add twice")
                        {
                            sptr<TestComponent> component2{component};
                            component_container->attachComponent(component2);
                            component_container->updateComponents();
                            CHECK(component->data_ == 2);
                            CHECK(component2->data_ == 2);
                            CHECK(component == component2);
                        }
                        */
        }
        /*
                SECTION("Withoout update")
                {
                    SECTION("Add twice")
                    {
                        sptr<TestComponent> component2{component};
                        component_container->attachComponent(component2);
                        CHECK(component == component2);
                    }
                }
                */
    }

    SECTION("Clear")
    {
        sptr<TestComponent> component{
            component_container.attachComponent<TestComponent>()};
        auto data_copy(component->data_);
        component_container.clearComponents();
        CHECK(data_copy == component->data_);
        CHECK(component_container.size() == 0U);
    }
}

namespace
{
struct TestComposedComponent
    : public ComponentBootStrap<TestComposedComponent, "Test">
//, TestComponent>
{
    static constexpr const core::str_view StaticTypeName{
        "TestComposedComponent"};

    int data_{0};

private:
    //    void update() override { ++data_; }
};

struct TestComposedComposedComponent
    : public ComponentBootStrap<TestComposedComposedComponent, "Test">
//    ,                          TestComposedComponent>
{
    static constexpr const core::str_view StaticTypeName{
        "TestComposedComposedComponent"};

    int data_{0};

private:
    //    void update() override { ++data_; }
};

struct TestComposedComponentRequirements
    : public ComponentBootStrap<TestComposedComponentRequirements, "Test">
// , TestComponent2,
//                           TestComponent3,
//                           TestComponent>
{
    static constexpr const core::str_view StaticTypeName{
        "TestComposedComponentRequirements"};

    int data_{0};

private:
    //    void update() override { ++data_; }
};
}  // namespace
   /*
   TEST_CASE("ComponentContainer::composed_component", "[ComponentContainer]")
   {
       // Create scenario for testing
       auto t_system{createSystemForTest<TestSceneManager>()};
       auto& scene_manager{t_system.system};
       rptr<ComponentContainer> component_container{scene_manager.rootSceneNode()};
       CHECK(component_container != nullptr);
       auto const baseNumComponents{component_container->components()};
   
       {
           sptr<TestComposedComponent> composed_component{
               component_container->attachComponent<TestComposedComponent>()};
           CHECK(composed_component == nullptr);
       }
   
       CHECK(component_container->components() == baseNumComponents);
   
       scene_manager.registerComponent<TestComposedComponent>();
   
       {
           sptr<TestComposedComponent> composed_component{
               component_container->attachComponent<TestComposedComponent>()};
           CHECK(composed_component == nullptr);
       }
   
       CHECK(component_container->components() == baseNumComponents);
       scene_manager.registerComponent<TestComponent>();
   
       CHECK(component_container->attachComponent<TestComposedComponent>() !=
             nullptr);
       CHECK(component_container->components() == baseNumComponents + 2U);
   
       CHECK(component_container->attachComponent<TestComponent>() != nullptr);
       CHECK(component_container->attachComponent<TestComposedComponent>() !=
             nullptr);
       CHECK(component_container->components() == baseNumComponents + 2U);
   }
   
   TEST_CASE("ComponentContainer::composed_composed_component",
             "[ComponentContainer]")
   {
       // Create scenario for testing
       auto t_system{createSystemForTest<TestSceneManager>()};
       rptr<ComponentContainer> component_container{
           t_system.system.rootSceneNode()};
       CHECK(component_container != nullptr);
       auto const baseNumComponents{component_container->components()};
       auto& scene_manager{t_system.system};
   
       CHECK(scene_manager.registerComponent<TestComposedComposedComponent>());
       CHECK(scene_manager.registerComponent<TestComposedComponent>());
       CHECK(scene_manager.registerComponent<TestComponent>());
   
       sptr<TestComposedComposedComponent> composed_component{
           component_container->attachComponent<TestComposedComposedComponent>()};
   
       CHECK(composed_component != nullptr);
       CHECK(
           component_container->componentOfType<TestComposedComposedComponent>() !=
           nullptr);
   
       CHECK(component_container->componentOfType<TestComponent>() != nullptr);
       CHECK(component_container->componentOfType<TestComposedComponent>() !=
             nullptr);
       CHECK(component_container->components() == baseNumComponents + 3U);
   
       CHECK(component_container->attachComponent<TestComponent>() != nullptr);
       CHECK(component_container->attachComponent<TestComposedComponent>() !=
             nullptr);
       CHECK(
           component_container->attachComponent<TestComposedComposedComponent>() !=
           nullptr);
       CHECK(component_container->components() == baseNumComponents + 3U);
   
       SECTION("ComponentRequirements")
       {
           ComponentSPtr<TestComposedComposedComponent> myComponent{
               component_container
                   ->attachComponent<TestComposedComposedComponent>()};
           CHECK(myComponent != nullptr);
   //        CHECK(myComponent->getComponent<TestComposedComponent>() != nullptr);
       }
   }
   
   TEST_CASE("ComponentContainer::composed_composed_component_with_str",
             "[ComponentContainer]")
   {
       auto t_system{createSystemForTest<TestSceneManager>()};
       rptr<ComponentContainer> component_container{
           t_system.system.rootSceneNode()};
       CHECK(component_container != nullptr);
       auto const baseNumComponents{component_container->components()};
       auto& scene_manager{t_system.system};
   
       CHECK(scene_manager.registerComponent<TestComposedComposedComponent>());
       CHECK(scene_manager.registerComponent<TestComposedComponent>());
       CHECK(scene_manager.registerComponent<TestComponent>());
   
       sptr<Component> composed_component{
           component_container->attachComponent("TestComposedComposedComponent")};
   
       CHECK(composed_component != nullptr);
       CHECK(component_container->componentOfType(
                 "TestComposedComposedComponent") != nullptr);
   
       CHECK(component_container->componentOfType("TestComponent") != nullptr);
       CHECK(component_container->componentOfType("TestComposedComponent") !=
             nullptr);
       CHECK(component_container->components() == baseNumComponents + 3U);
   
       CHECK(component_container->attachComponent("TestComponent") != nullptr);
       CHECK(component_container->attachComponent("TestComposedComponent") !=
             nullptr);
       CHECK(component_container->attachComponent(
                 "TestComposedComposedComponent") != nullptr);
       CHECK(component_container->components() == baseNumComponents + 3U);
   
       SECTION("ComponentRequirements")
       {
           ComponentSPtr<Component> myComponent{
               component_container->attachComponent(
                   "TestComposedComposedComponent")};
           CHECK(myComponent != nullptr);
           ComponentSPtr<TestComposedComposedComponent> myComponent2{
               core::dynamic_pointer_cast<TestComposedComposedComponent>(
                   myComponent)};
           CHECK(myComponent2);
   //        CHECK(myComponent2->getComponent<TestComposedComponent>() != nullptr);
       }
   }
   
   TEST_CASE("ComponentContainer::three_components_no_req", "[ComponentContainer]")
   {
       auto t_system{createSystemForTest<TestSceneManager>()};
       rptr<ComponentContainer> component_container{
           t_system.system.rootSceneNode()};
       CHECK(component_container != nullptr);
       auto const baseNumComponents{component_container->components()};
       auto& scene_manager{t_system.system};
   
       CHECK(scene_manager.registerComponent<TestComponent2>());
       CHECK(scene_manager.registerComponent<TestComponent3>());
       CHECK(scene_manager.registerComponent<TestComponent>());
   
       sptr<TestComponent> test_component{
           component_container->attachComponent<TestComponent>()};
       sptr<TestComponent2> test_component2{
           component_container->attachComponent<TestComponent2>()};
       sptr<TestComponent3> test_component3{
           component_container->attachComponent<TestComponent3>()};
   
       CHECK(component_container->components() == baseNumComponents + 3U);
   
       CHECK(test_component != nullptr);
       CHECK(test_component2 != nullptr);
       CHECK(test_component3 != nullptr);
   }
   
   TEST_CASE("ComponentContainer::three_components_req_three",
             "[ComponentContainer]")
   {
       auto t_system{createSystemForTest<TestSceneManager>()};
       rptr<ComponentContainer> component_container{
           t_system.system.rootSceneNode()};
       CHECK(component_container != nullptr);
       auto const baseNumComponents{component_container->components()};
       auto& scene_manager{t_system.system};
   
       CHECK(scene_manager.registerComponent<TestComponent2>());
       CHECK(scene_manager.registerComponent<TestComponent3>());
       CHECK(scene_manager.registerComponent<TestComponent>());
       CHECK(scene_manager.registerComponent<TestComposedComponentRequirements>());
   
       sptr<TestComposedComponentRequirements> test_component{
           component_container
               ->attachComponent<TestComposedComponentRequirements>()};
       CHECK(component_container->components() == baseNumComponents + 4U);
       sptr<TestComponent> test_component_{
           component_container->attachComponent<TestComponent>()};
       sptr<TestComponent2> test_component2{
           component_container->attachComponent<TestComponent2>()};
       sptr<TestComponent3> test_component3{
           component_container->attachComponent<TestComponent3>()};
       CHECK(component_container->components() == baseNumComponents + 4U);
   
       CHECK(test_component != nullptr);
       CHECK(test_component_ != nullptr);
       CHECK(test_component2 != nullptr);
       CHECK(test_component3 != nullptr);
   
       SECTION("ComponentRequirements")
       {
           CHECK(test_component->getComponent<TestComponent>() != nullptr);
           CHECK(test_component->getComponent<TestComponent2>() != nullptr);
           CHECK(test_component->getComponent<TestComponent3>() != nullptr);
   
           ComponentSPtr<TestComposedComponentRequirements const>
               const_test_component{core::dynamic_pointer_cast<
                   TestComposedComponentRequirements const>(test_component)};
           CHECK(const_test_component->getComponent<TestComponent const>() !=
                 nullptr);
           ComponentSPtr<TestComponent const> b =
               const_test_component->getComponent<TestComponent const>();
           CHECK(b != nullptr);
           CHECK(const_test_component->getComponent<TestComponent2>() != nullptr);
           CHECK(const_test_component->getComponent<TestComponent3>() != nullptr);
   
           static_assert(
               std::is_same_v<
                   decltype(const_test_component->getComponent<TestComponent2>()),
                   core::sptr<TestComponent2 const>>);
           static_assert(
               std::is_same_v<
                   decltype(const_test_component->getComponent<TestComponent3>()),
                   core::sptr<TestComponent3 const>>);
       }
   }
   */