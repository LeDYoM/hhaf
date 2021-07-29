#include "catch.hpp"

#include <htypes/include/types.hpp>
#include <haf/include/scene/scenenode.hpp>
#include <haf/include/scene/scene.hpp>
#include <haf/include/component/component_container.hpp>
#include <haf/include/component/icomponent.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::component;

struct TestComponent : public IComponent
{
    int data_{0};

    sptr<TestComponent> addAnother()
    {
        return attachedNode()->components().component<TestComponent>();
    }

private:
    void update() override { ++data_; }
};

TEST_CASE("haf::scene::ComponentContainer", "[ComponentContainer][constructor]")
{
    // Create scenario for testing
    sptr<ComponentContainer> component_container_no_parent(
        msptr<ComponentContainer>(nullptr));

    SECTION("Add component")
    {
        sptr<TestComponent> component =
            component_container_no_parent->component<TestComponent>();

        sptr<TestComponent> component_not_created =
            component_container_no_parent->component<TestComponent>();
        CHECK(component == component_not_created);

        SECTION("Update")
        {
            component_container_no_parent->updateComponents();
            CHECK(component->data_ == 1);

            SECTION("Try Add twice")
            {
                sptr<TestComponent> component2 = component;
                component_container_no_parent->component(
                    component2);
                component_container_no_parent->updateComponents();
                CHECK(component->data_ == 2);
                CHECK(component2->data_ == 2);
                CHECK(component == component2);
            }
        }

        SECTION("Withoout update")
        {
            SECTION("Add twice")
            {
                sptr<TestComponent> component2 = component;
                component_container_no_parent->component(
                    component2);
                CHECK(component == component2);
            }
        }
    }

    SECTION("Clear")
    {
        sptr<TestComponent> component =
            component_container_no_parent->component<TestComponent>();
        auto data_copy(component->data_);
        component_container_no_parent->clearComponents();
        CHECK(data_copy == component->data_);
    }
}
