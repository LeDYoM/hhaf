#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <mtypes/include/basic_property.hpp>

using namespace mtps;

TEST_CASE("BasicProperty::BasicProperty", "[mtypes][property][BasicProperty]")
{
    {
        BasicProperty<int> p;
        CHECK(p() == 0);
        CHECK(p.get() == 0);
    }

    {
        BasicProperty<int> p(50);
        CHECK(p() == 50);
        CHECK(p.get() == 50);
    }

    {
        BasicProperty<int> p{5};
        CHECK(p() == 5);
        CHECK(p.get() == 5);
    }

}

TEST_CASE("BasicProperty::set", "[mtypes][property][BasicProperty]")
{
    BasicProperty<int> p;
    CHECK(p() == 0);
    CHECK(p.get() == 0);
    CHECK(p.set(10));
    CHECK(p() == 10);
    CHECK(p.get() == 10);
}

struct Tag {};

TEST_CASE("BasicProperty::toIProperty", "[mtypes][property][BasicProperty]")
{
    BasicProperty<int, Tag> p;
    CHECK(p() == 0);
    CHECK(p.get() == 0);
    CHECK(p.set(10));
    CHECK(p() == 10);
    CHECK(p.get() == 10);
    CHECK_FALSE(p.set(10));
    CHECK(p() == 10);
    CHECK(p.get() == 10);

    auto ip = dynamic_cast<IProperty<int, Tag>*>(&p);
    CHECK(ip->set(50));
    CHECK_FALSE(ip->set(50));
    CHECK(ip->get() == 50);
}

