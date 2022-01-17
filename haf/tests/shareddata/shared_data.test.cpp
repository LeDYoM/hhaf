#include "catch.hpp"

#include <htypes/include/types.hpp>
#include "shareddata/shared_data_system.hpp"
#include <haf/include/shareddata/ishared_data.hpp>
#include "include/shareable_test_data.hpp"
#include "system_test_utils.hpp"

using namespace htps;
using namespace haf::shdata;

TEST_CASE("SharedData::SharedData", "[haf][shareddatasystem]")
{
    auto test_shared_data = makeTestSystem<TestSharedDataSystem>();

    ShareableTestData shareable_test_data;

    auto ssv{test_shared_data->getSubSystemViewer()};

    SECTION("Retrieve from empty")
    {
        auto shared_data{ssv.subSystem<ISharedData>()};
        bool const retrieve_result = shared_data->retrieve(
            ShareableTestData::address(), shareable_test_data);

        CHECK_FALSE(retrieve_result);
    }

    SECTION("Store and retrieve")
    {
        shareable_test_data.a = 42;
        shareable_test_data.b = 123.33F;
        shareable_test_data.c = "hello test";

        auto shared_data{ssv.subSystem<ISharedData>()};
        bool const store_result = shared_data->store(
            ShareableTestData::address(), shareable_test_data);

        CHECK(store_result);

        ShareableTestData result{};

        CHECK(result.a == 0);
        CHECK(result.b == 0.0F);
        CHECK(result.c == "");

        bool const retrieve_result{
            shared_data->retrieve(ShareableTestData::address(), result)};

        CHECK(retrieve_result);
        CHECK(result.a == 42);
        CHECK(result.b == 123.33F);
        CHECK(result.c == "hello test");
    }
}
