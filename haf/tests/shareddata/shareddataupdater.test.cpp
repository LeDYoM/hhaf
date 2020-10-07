#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <shareddata/i_include/shareddatasystem.hpp>
#include <haf/shareddata/include/shareddataupdater.hpp>
#include "include/shareable_test_data.hpp"
#include "test_utils.hpp"

using namespace mtps;
using namespace haf::shdata;

TEST_CASE("SharedDataSystemUpdater::SharedDataSystemUpdater",
          "[haf][shareddatasystem]")
{
    auto const test_shared_data = makeTestSystem<TestSharedDataSystem>();

    ShareableTestData shareable_test_data;

    auto dwc{test_shared_data->get()};

    SECTION("View from empty")
    {
        auto shared_data_wrapper{dwc.dataWrapper<SharedDataUpdater<ShareableTestData>>()};
        bool const retrieve_result = shared_data_wrapper->retrieve(
            ShareableTestData::address(), shareable_test_data);

        CHECK_FALSE(retrieve_result);

        auto update_result = shared_data_wrapper->update(
            ShareableTestData::address());

        CHECK_FALSE(update_result);
    }

    SECTION("Store and update")
    {
        shareable_test_data.a = 42;
        shareable_test_data.b = 123.33F;
        shareable_test_data.c = "hello test";

        auto shared_data_wrapper{dwc.dataWrapper<SharedDataUpdater<ShareableTestData>>()};
        bool const store_result = shared_data_wrapper->store(
            ShareableTestData::address(), shareable_test_data);

        CHECK(store_result);

        ShareableTestData result{};

        CHECK(result.a == 0);
        CHECK(result.b == 0.0F);
        CHECK(result.c == "");

        SECTION("Update")
        {
            auto shared_data_wrapper_internal{
                dwc.dataWrapper<SharedDataUpdater<ShareableTestData>>()};

            auto update_result = shared_data_wrapper_internal->update(
                ShareableTestData::address());

            CHECK(update_result);
            CHECK(update_result->a == 42);
            CHECK(update_result->b == 123.33F);
            CHECK(update_result->c == "hello test");
        }
    }
}
