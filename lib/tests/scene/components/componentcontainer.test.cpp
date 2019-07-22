#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/components/componentcontainer.hpp>
#include <lib/scene/components/icomponent.hpp>

using namespace lib;
using namespace lib::scene;

struct TestComponent : public IComponent
{
    int data_{ 0 };

    sptr<TestComponent> addAnother()
    {
        return attachedNode()->addComponentOfType<TestComponent>();
    }
private:
    void update() override
    {
        ++data_;
    }
};

TEST_CASE("lib::scene::ComponentContainer", "[ComponentContainer][constructor]")
{
    // Create scenario for testing
    sptr<ComponentContainer> component_container_no_parent(msptr<ComponentContainer>());

    SECTION("Add component")
    {
        sptr<TestComponent> component = component_container_no_parent->addComponentOfType<TestComponent>();

        SECTION("Update")
        {
            component_container_no_parent->updateComponents();
            CHECK(component->data_ == 1);

            SECTION("Add twice")
            {
                sptr<TestComponent> component2 = component;
                component_container_no_parent->ensureComponentOfType(component2);
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
                component_container_no_parent->ensureComponentOfType(component2);
                CHECK(component == component2);
            }
        }
    }

    SECTION("Clear")
    {
        sptr<TestComponent> component = component_container_no_parent->addComponentOfType<TestComponent>();
        auto data_copy(component->data_);
        component_container_no_parent->clearComponents();
        CHECK(data_copy == component->data_);
    }
}
