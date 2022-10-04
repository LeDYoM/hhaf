#include "catch.hpp"

#include <htypes/include/types.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/scene.hpp>
#include <haf/include/component/component_container.hpp>
#include <haf/include/component/icomponent.hpp>
#include <haf/include/component/composed_component.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::component;

struct TestComponent : public IComponent
{
    int data_{0};

private:
    void update() override { ++data_; }
};

TEST_CASE("haf::scene::ComponentContainer", "[ComponentContainer][constructor]")
{
    // Create scenario for testing
    scene::SceneNode sceneNode{nullptr, "TestSceneNode"};
    rptr<ComponentContainer> component_container{&sceneNode};

    SECTION("Add component")
    {
        sptr<TestComponent> component{
            component_container->component<TestComponent>()};

        sptr<TestComponent> component_other{
            component_container->component<TestComponent>()};
        CHECK(component == component_other);

        SECTION("Update")
        {
            component_container->updateComponents();
            CHECK(component->data_ == 1);

            SECTION("Try Add twice")
            {
                sptr<TestComponent> component2{component};
                component_container->component(component2);
                component_container->updateComponents();
                CHECK(component->data_ == 2);
                CHECK(component2->data_ == 2);
                CHECK(component == component2);
            }
        }

        SECTION("Withoout update")
        {
            SECTION("Add twice")
            {
                sptr<TestComponent> component2{component};
                component_container->component(component2);
                CHECK(component == component2);
            }
        }
    }

    SECTION("Clear")
    {
        sptr<TestComponent> component{
            component_container->component<TestComponent>()};
        auto data_copy(component->data_);
        component_container->clearComponents();
        CHECK(data_copy == component->data_);
    }
}

struct TestComposedComponent : public ComposedComponent<TestComponent>
{
    int data_{0};

private:
    void update() override { ++data_; }
};

struct TestComposedComposedComponent
    : public ComposedComponent<TestComposedComponent>
{
    int data_{0};

private:
    void update() override { ++data_; }
};

TEST_CASE("ComponentContainer::composed_component", "[ComponentContainer]")
{
    // Create scenario for testing
    scene::SceneNode sceneNode{nullptr, "TestSceneNode"};
    rptr<ComponentContainer> component_container{&sceneNode};
    CHECK(component_container->components() == 0U);

    sptr<TestComposedComponent> composed_component{
        component_container->component<TestComposedComponent>()};

    CHECK(component_container->componentOfType<TestComponent>() != nullptr);
    CHECK(component_container->components() == 2U);

    CHECK(component_container->component<TestComponent>() != nullptr);
    CHECK(component_container->component<TestComposedComponent>() != nullptr);
    CHECK(component_container->components() == 2U);
}

TEST_CASE("ComponentContainer::composed_composed_component",
          "[ComponentContainer]")
{
    // Create scenario for testing
    scene::SceneNode sceneNode{nullptr, "TestSceneNode"};
    rptr<ComponentContainer> component_container{&sceneNode};
    CHECK(component_container->components() == 0U);

    sptr<TestComposedComposedComponent> composed_component{
        component_container->component<TestComposedComposedComponent>()};

    CHECK(component_container->componentOfType<TestComponent>() != nullptr);
    CHECK(component_container->componentOfType<TestComposedComponent>() !=
          nullptr);
    CHECK(
        component_container->componentOfType<TestComposedComposedComponent>() !=
        nullptr);
    CHECK(component_container->components() == 3U);

    CHECK(component_container->component<TestComponent>() != nullptr);
    CHECK(component_container->component<TestComposedComponent>() != nullptr);
    CHECK(component_container->component<TestComposedComposedComponent>() !=
          nullptr);
    CHECK(component_container->components() == 3U);

    CHECK(component_container->componentOfType<TestComposedComposedComponent>()
              ->composedComponent()
              ->composedComponent()
              ->attachedNode() == &sceneNode);
}
