#include "catch.hpp"

#include <mtypes/include/lockablevector.hpp>
#include <mtypes/include/types.hpp>
#include <mtypes/include/lockablevector.hpp>

using namespace lib;

TEST_CASE("LocableVector constructors", "[LocableVector]")
{
    LockableVector<u32> locable_vector;
    auto m(locable_vector.current());

    CHECK(m.size() == 0);
    CHECK(m.empty());
    CHECK(m.capacity() == 0);

}

TEST_CASE("LocableVector lock", "[LocableVector]")
{
    LockableVector<u32> locable_vector;
    auto m(locable_vector.current());

    SECTION("Add elements")
    {
        locable_vector.push_back(0);
        locable_vector.push_back(1);
        locable_vector.push_back(2);
        locable_vector.push_back(3);
        locable_vector.push_back(4);

        // After adding but not updating, the visible vector
        // is still empty.
        CHECK(locable_vector.are_pending_adds());
        CHECK(locable_vector.pending_add() == 5);

        // The call to current() updates implicity.
        CHECK(locable_vector.current().size() == 5);

        SECTION("Add")
        {
            locable_vector.update();
            CHECK(locable_vector.current().size() == 5);
            CHECK_FALSE(locable_vector.are_pending_adds());
            CHECK(locable_vector.pending_add() == 0);
            locable_vector.push_back(5);
            locable_vector.emplace_back(6);
            CHECK(locable_vector.current().size() == 7);
            // Update does not affect in this case
            locable_vector.update();
            CHECK(locable_vector.current().size() == 7);
            CHECK_FALSE(locable_vector.are_pending_adds());
            CHECK(locable_vector.pending_add() == 0);
        }

        SECTION("Remove")
        {
            locable_vector.remove_value(1);
            CHECK(locable_vector.are_pending_removes());
            CHECK(locable_vector.pending_remove() == 1);
            CHECK(locable_vector.current().size() == 4);
            locable_vector.remove_value(1);
            CHECK(locable_vector.current().size() == 4);
        }
    }
}
