#include "catch.hpp"

#include <htypes/include/types.hpp>
#include <htypes/include/propertystate.hpp>

using namespace htps;

TEST_CASE("PropertyState", "[htypes][property][state]")
{
    PropertyState<int> a;
    CHECK(a.hasChanged());
    CHECK(a.readResetHasChanged());
    CHECK_FALSE(a.hasChanged());

    PropertyState<htps::sptr<s32>> b;
    auto t = htps::msptr<s32>(5);
    b.set(t);
    CHECK(*(t.get()) == 5);
    CHECK(*(b.get()) == 5);
    t = msptr<s32>(10);

    CHECK(b.readResetHasChanged());
    CHECK_FALSE(b.readResetHasChanged());

    b.set(std::move(t));
    CHECK(t.get() == nullptr);
    CHECK(*(b.get()) == 10);

    CHECK(b.readResetHasChanged());
    CHECK_FALSE(b.readResetHasChanged());

    PropertyState<s32> c;
    CHECK(c.readResetHasChanged());
    CHECK_FALSE(c.readResetHasChanged());

    c = 1;
    CHECK(c.readResetHasChanged());
    CHECK_FALSE(c.readResetHasChanged());
    CHECK(c() == 1);
}
