#include "catch.hpp"

#include <mtypes/include/connection.hpp>
#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>

using namespace mtps;

struct TargetConnection
{
    s32 data{0};

    function<void(s32)> receiver_lambda = [this](s32 d) { data = d; };

    void receiver_method(s32 d) { data = d; }
};

TEST_CASE("emitter::emitter with lambda connect", "[emitter][connection]")
{
    emitter<s32> test_emitter;
    TargetConnection t_connection;

    // Check is empty
    CHECK(test_emitter.size() == 0U);
    CHECK(test_emitter.empty());

    // Connect to the target receiver
    test_emitter.connect(t_connection.receiver_lambda);
    CHECK(t_connection.data == 0);
    CHECK(test_emitter.size() == 1U);
    CHECK(!test_emitter.empty());

    // Perform test of the connection
    test_emitter(5);
    CHECK(t_connection.data == 5);
    test_emitter(67);
    CHECK(t_connection.data == 67);

    // Check that an invalid parameter does not disconnect
    TargetConnection t_connection2;
    CHECK_FALSE(test_emitter.disconnect(t_connection2.receiver_lambda));
    CHECK(test_emitter.size() == 1U);
    CHECK(!test_emitter.empty());

    test_emitter(9123);
    CHECK(t_connection.data == 9123);

    // Now perform a correct disconnection
    CHECK(test_emitter.disconnect(t_connection.receiver_lambda));

    // Check is empty after disconnection
    CHECK(test_emitter.size() == 0U);
    CHECK(test_emitter.empty());

    // After disconnection, calls to the emission does not affect the
    // previous connected object
    test_emitter(100);
    CHECK(t_connection.data == 9123);

    // Test reconnection to the same object works
    test_emitter += t_connection.receiver_lambda;
    CHECK(test_emitter.size() == 1U);
    CHECK(!test_emitter.empty());
    test_emitter(200);
    CHECK(t_connection.data == 200);
    test_emitter -= t_connection.receiver_lambda;
    CHECK(test_emitter.size() == 0U);
    CHECK(test_emitter.empty());
}

TEST_CASE("emitter::emitter with member pointer connect",
          "[emitter][connection]")
{
    emitter<s32> test_emitter;
    TargetConnection t_connection;

    // Check is empty
    CHECK(test_emitter.size() == 0U);
    CHECK(test_emitter.empty());

    // Connect to the target receiver
    test_emitter.connect(
        make_function(&t_connection, &TargetConnection::receiver_method));
    CHECK(t_connection.data == 0);
    CHECK(test_emitter.size() == 1U);
    CHECK(!test_emitter.empty());

    // Perform test of the connection
    test_emitter(5);
    CHECK(t_connection.data == 5);
    test_emitter(67);
    CHECK(t_connection.data == 67);

    // Check that an invalid parameter does not disconnect
    TargetConnection t_connection2;
    CHECK_FALSE(test_emitter.disconnect(t_connection2.receiver_lambda));
    CHECK(test_emitter.size() == 1U);
    CHECK(!test_emitter.empty());

    test_emitter(9123);
    CHECK(t_connection.data == 9123);

    // Now perform a correct disconnection
    CHECK(test_emitter.disconnect(
        make_function(&t_connection, &TargetConnection::receiver_method)));

    // Check is empty after disconnection
    CHECK(test_emitter.size() == 0U);
    CHECK(test_emitter.empty());

    // After disconnection, calls to the emission does not affect the
    // previous connected object
    test_emitter(100);
    CHECK(t_connection.data == 9123);

    // Test reconnection to the same object works
    test_emitter +=
        make_function(&t_connection, &TargetConnection::receiver_method);
    CHECK(test_emitter.size() == 1U);
    CHECK(!test_emitter.empty());
    test_emitter(200);
    CHECK(t_connection.data == 200);
    test_emitter -=
        make_function(&t_connection, &TargetConnection::receiver_method);
    CHECK(test_emitter.size() == 0U);
    CHECK(test_emitter.empty());
}

TEST_CASE("connection::connection", "[emitter][connection][iconnection")
{
    emitter<s32> test_emitter;
    TargetConnection t_connection;

    {
        connection<s32> connection{test_emitter, t_connection.receiver_lambda};

        test_emitter(700);
        CHECK(t_connection.data == 700);
    }

    // The connection was destroyed, so triggering it does nothing.
    test_emitter(900);
    CHECK(t_connection.data == 700);
}
