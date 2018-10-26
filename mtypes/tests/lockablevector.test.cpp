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
    LockableVector<u32> lockable_vector;
    auto m(lockable_vector.current());

    SECTION("Add elements")
    {
        lockable_vector.push_back(0);
        lockable_vector.push_back(1);
        lockable_vector.push_back(2);
        lockable_vector.push_back(3);
        lockable_vector.push_back(4);

        // After adding but not updating, the visible vector
        // is still empty.
        CHECK(lockable_vector.are_pending_adds());
        CHECK(lockable_vector.pending_add() == 5);

        // The call to current() updates implicity.
        CHECK(lockable_vector.deferred_current().size() == 0);
        CHECK(lockable_vector.current().size() == 5);

        SECTION("Add")
        {
            lockable_vector.update();
            CHECK(lockable_vector.deferred_current() == lockable_vector.current());

            CHECK(lockable_vector.current().size() == 5);
            CHECK_FALSE(lockable_vector.are_pending_adds());
            CHECK(lockable_vector.pending_add() == 0);
            lockable_vector.push_back(5);
            lockable_vector.emplace_back(6);
            CHECK(lockable_vector.current().size() == 7);

            // Update does not affect in this case
            lockable_vector.update();
            CHECK(lockable_vector.current().size() == 7);
            CHECK_FALSE(lockable_vector.are_pending_adds());
            CHECK(lockable_vector.pending_add() == 0);
            CHECK(lockable_vector.deferred_current() == lockable_vector.current());
        }

        SECTION("Remove")
        {
            lockable_vector.remove_value(1);
            CHECK(lockable_vector.are_pending_removes());
            CHECK(lockable_vector.pending_remove() == 1);
            const auto v(lockable_vector.deferred_current());
            CHECK_FALSE(v == lockable_vector.current());
            CHECK(lockable_vector.current().size() == 4);
            lockable_vector.remove_value(1);
            CHECK(lockable_vector.deferred_current() == lockable_vector.current());
            CHECK(lockable_vector.current().size() == 4);
        }

        SECTION("Mix Add and Remove (KISS version)")
        {
            lockable_vector.remove_value(1);
            lockable_vector.push_back(5);
            lockable_vector.emplace_back(6);

            CHECK(lockable_vector.are_pending_removes());
            CHECK(lockable_vector.pending_remove() == 1);
            CHECK(lockable_vector.are_pending_adds());
            CHECK(lockable_vector.pending_add() == 2);

            CHECK(lockable_vector.current().size() == 6);
            CHECK_FALSE(lockable_vector.are_pending_removes());
            CHECK(lockable_vector.pending_remove() == 0);
            CHECK_FALSE(lockable_vector.are_pending_adds());
            CHECK(lockable_vector.pending_add() == 0);
        }

        SECTION("Mix Add and Remove (more complicated version)")
        {
            lockable_vector.remove_value(1);
            lockable_vector.push_back(5);
            lockable_vector.emplace_back(6);

            CHECK(lockable_vector.are_pending_removes());
            CHECK(lockable_vector.pending_remove() == 1);
            CHECK(lockable_vector.are_pending_adds());
            CHECK(lockable_vector.pending_add() == 2);

            CHECK(lockable_vector.current().size() == 6);
            CHECK_FALSE(lockable_vector.are_pending_removes());
            CHECK(lockable_vector.pending_remove() == 0);
            CHECK_FALSE(lockable_vector.are_pending_adds());
            CHECK(lockable_vector.pending_add() == 0);
        }

    }
}
