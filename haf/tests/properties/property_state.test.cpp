#include "catch_include.hpp"

#include <haf/include/core/types.hpp>
#include <haf/include/properties/property_state.hpp>

using namespace haf;
using namespace haf::prop;
using namespace htps;

TEST_CASE("PropertyState", "[htypes][property][state]")
{
    PropertyState<int> a;
    CHECK(a.hasChanged());
    CHECK(a.readResetHasChanged());
    CHECK_FALSE(a.hasChanged());

    PropertyState<core::sptr<s32>> b;
    auto t = core::msptr<s32>(5);
    b      = t;
    CHECK(*(t.get()) == 5);
    CHECK(*(b()) == 5);
    t = msptr<s32>(10);

    CHECK(b.readResetHasChanged());
    CHECK_FALSE(b.readResetHasChanged());

    b = htps::move(t);
    CHECK(*(b()) == 10);

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

struct Movable
{
    int a;
    bool operator==(Movable const& rhs) const noexcept
    {
        return a == rhs.a;
    }
};

TEST_CASE("PropertyState::assignIfDifferent", "[htypes][property][state]")
{
    SECTION("By value")
    {
        PropertyState<Movable> temp;
        temp = Movable{1};
        temp.resetHasChanged();
        CHECK_FALSE(temp.hasChanged());
        CHECK(temp().a == 1);

        Movable to_move{1};
        temp.assignIfDifferent(htps::move(to_move));
        CHECK_FALSE(temp.hasChanged());
        CHECK_FALSE(temp.readResetHasChanged());
        CHECK(temp().a == 1);

        to_move.a = 10;
        temp.assignIfDifferent(htps::move(to_move));
        CHECK(temp.hasChanged());
        CHECK(temp.readResetHasChanged());
        CHECK(temp().a == 10);
    }

    SECTION("Const reference")
    {
        PropertyState<int> temp;
        temp = 1;
        temp.resetHasChanged();
        CHECK_FALSE(temp.hasChanged());
        CHECK(temp() == 1);

        temp.assignIfDifferent(1);
        CHECK_FALSE(temp.hasChanged());
        CHECK_FALSE(temp.readResetHasChanged());
        CHECK(temp() == 1);

        temp.assignIfDifferent(10);
        CHECK(temp.hasChanged());
        CHECK(temp.readResetHasChanged());
        CHECK(temp() == 10);
    }
}
