#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/lockablevector.hpp>

using namespace lib;

TEST_CASE("LocableVector constructors", "[LocableVector]")
{
    LockableVector<u32> locable_vector;
    auto m(locable_vector.current());
}

TEST_CASE("LockableVector", "[LockableVector]")
{
    LockableVector<u32> lockable_vector;
    auto m(lockable_vector.current());

    CHECK(m.size() == 0U);
    CHECK(m.empty());
    CHECK(m.capacity() == 0U);

    SECTION("Add elements")
    {
        lockable_vector.push_back(0U);
        lockable_vector.push_back(1U);
        lockable_vector.push_back(2U);
        lockable_vector.push_back(3U);
        lockable_vector.push_back(4U);

        // After adding but not updating, the visible vector
        // is still empty.
        CHECK(lockable_vector.are_pending_adds());
        CHECK(lockable_vector.pending_add() == 5U);

        // The call to current() updates implicity.
        CHECK(lockable_vector.deferred_current().size() == 0U);
        CHECK(lockable_vector.current().size() == 5U);

        SECTION("Add")
        {
            lockable_vector.update();
            CHECK(lockable_vector.deferred_current() == lockable_vector.current());

            CHECK(lockable_vector.current().size() == 5U);
            CHECK_FALSE(lockable_vector.are_pending_adds());
            CHECK(lockable_vector.pending_add() == 0U);
            lockable_vector.push_back(5U);
            lockable_vector.emplace_back(6U);
            CHECK(lockable_vector.current().size() == 7U);

            // Update does not affect in this case
            lockable_vector.update();
            CHECK(lockable_vector.current().size() == 7U);
            CHECK_FALSE(lockable_vector.are_pending_adds());
            CHECK(lockable_vector.pending_add() == 0U);
            CHECK(lockable_vector.deferred_current() == lockable_vector.current());
        }

        SECTION("Remove")
        {
            lockable_vector.erase_values(1);
            CHECK(lockable_vector.are_pending_removes());
            CHECK(lockable_vector.pending_remove() == 1U);
            const auto v(lockable_vector.deferred_current());
            CHECK_FALSE(v == lockable_vector.current());
            CHECK(lockable_vector.current().size() == 4U);
            lockable_vector.erase_values(1U);
            CHECK(lockable_vector.deferred_current() == lockable_vector.current());
            CHECK(lockable_vector.current().size() == 4U);
        }

        SECTION("Mix Add and Remove (KISS version)")
        {
            lockable_vector.erase_values(1U);
            lockable_vector.push_back(5U);
            lockable_vector.emplace_back(6U);

            CHECK(lockable_vector.are_pending_removes());
            CHECK(lockable_vector.pending_remove() == 1U);
            CHECK(lockable_vector.are_pending_adds());
            CHECK(lockable_vector.pending_add() == 2U);

            CHECK(lockable_vector.current().size() == 6U);
            CHECK_FALSE(lockable_vector.are_pending_removes());
            CHECK(lockable_vector.pending_remove() == 0U);
            CHECK_FALSE(lockable_vector.are_pending_adds());
            CHECK(lockable_vector.pending_add() == 0U);
        }

        SECTION("Mix Add and Remove (more complicated version)")
        {
            lockable_vector.erase_values(1U);
            lockable_vector.push_back(5U);
            lockable_vector.emplace_back(6U);

            SECTION("LockableVector::next")
            {
                vector<u32> next_one(lockable_vector.next());

                CHECK_FALSE(next_one.empty());
                CHECK(next_one.size() != lockable_vector.deferred_current().size());
                auto sz(next_one.size());
                auto rsv(next_one.capacity());

                lockable_vector.push_back(9U);
                lockable_vector.erase_values(3U);

                CHECK(next_one.size() == sz);
                CHECK(next_one.capacity() == rsv);
            }

            SECTION("More mixing")
            {
                CHECK(lockable_vector.are_pending_removes());
                CHECK(lockable_vector.pending_remove() == 1U);
                CHECK(lockable_vector.are_pending_adds());
                CHECK(lockable_vector.pending_add() == 2U);

                CHECK(lockable_vector.current().size() == 6U);
                CHECK_FALSE(lockable_vector.are_pending_removes());
                CHECK(lockable_vector.pending_remove() == 0U);
                CHECK_FALSE(lockable_vector.are_pending_adds());
                CHECK(lockable_vector.pending_add() == 0U);
            }
        }
    }
}
