#include "catch.hpp"

#include <haf/include/core/types.hpp>
#include <haf/include/properties/iproperty.hpp>
#include <haf/include/properties/basic_property.hpp>

using namespace haf;
using namespace haf::prop;

TEST_CASE("BasicProperty::BasicProperty", "[htypes][property][BasicProperty]")
{
    {
        BasicProperty<int> p;
        CHECK(p() == 0);
    }

    {
        BasicProperty<int> p(50);
        CHECK(p() == 50);
    }

    {
        BasicProperty<int> p{5};
        CHECK(p() == 5);
    }
}

TEST_CASE("BasicProperty::set", "[htypes][property][BasicProperty]")
{
    BasicProperty<int> p;
    CHECK(p() == 0);
    p = 10;
    CHECK(p() == 10);
}

TEST_CASE("BasicProperty::toIProperty", "[htypes][property][BasicProperty]")
{
    BasicProperty<int> p;
    CHECK(p() == 0);
    p = 10;
    CHECK(p() == 10);

    auto ip = dynamic_cast<IProperty<int>*>(&p);
    (*ip) = 50;
    CHECK((*ip)() == 50);
}
