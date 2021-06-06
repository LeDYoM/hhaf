#include "catch.hpp"

#include <htypes/include/types.hpp>
#include "shareddata/shareddatasystem.hpp"
#include <haf/include/shareddata/shareddataupdater.hpp>
#include <haf/include/shareddata/shareddataviewer.hpp>
#include "include/shareable_test_data.hpp"
#include "system_test_utils.hpp"

using namespace htps;
using namespace haf::shdata;

TEST_CASE("SharedDataSystemUpdater::SharedDataSystemUpdater",
          "[haf][shareddatasystem]")
{
    auto const test_shared_data = makeTestSystem<TestSharedDataSystem>();

    ShareableTestData shareable_test_data;

    auto dwc{test_shared_data->get()};

    SECTION("View from empty")
    {
        auto shared_data_wrapper{
            dwc.dataWrapper<SharedDataUpdater<ShareableTestData>>()};
        bool const retrieve_result = shared_data_wrapper->retrieve(
            ShareableTestData::address(), shareable_test_data);

        CHECK_FALSE(retrieve_result);

        auto update_result =
            shared_data_wrapper->update(ShareableTestData::address());

        CHECK_FALSE(update_result);
    }

    SECTION("Store and update")
    {
        shareable_test_data.a = 42;
        shareable_test_data.b = 123.33F;
        shareable_test_data.c = "hello test";

        auto shared_data_wrapper{
            dwc.dataWrapper<SharedDataUpdater<ShareableTestData>>()};
        bool const store_result = shared_data_wrapper->store(
            ShareableTestData::address(), shareable_test_data);

        CHECK(store_result);

        SECTION("Update normal")
        {
            {
                auto shared_data_wrapper_internal{
                    dwc.dataWrapper<SharedDataUpdater<ShareableTestData>>()};

                auto update_result = shared_data_wrapper_internal->update(
                    ShareableTestData::address());

                CHECK(update_result != nullptr);
                CHECK(update_result->a == 42);
                CHECK(update_result->b == 123.33F);
                CHECK(update_result->c == "hello test");

                update_result->a = 64;
                update_result->b = 552.125F;
                update_result->c = "updated!";
            }

            {
                auto shared_data_wrapper_internal{
                    dwc.dataWrapper<SharedDataViewer<ShareableTestData>>()};

                auto update_result = shared_data_wrapper_internal->view(
                    ShareableTestData::address());

                CHECK(update_result);
                CHECK(update_result->a == 64);
                CHECK(update_result->b == 552.125F);
                CHECK(update_result->c == "updated!");
            }
        }

        SECTION("Update commit")
        {
            auto shared_data_wrapper_internal{
                dwc.dataWrapper<SharedDataUpdater<ShareableTestData>>()};

            auto update_result = shared_data_wrapper_internal->update(
                ShareableTestData::address());

            CHECK(update_result != nullptr);
            CHECK(update_result->a == 42);
            CHECK(update_result->b == 123.33F);
            CHECK(update_result->c == "hello test");

            update_result->a = 64;
            update_result->b = 552.125F;
            update_result->c = "updated!";

            CHECK(shared_data_wrapper_internal->commit());
            CHECK_FALSE(shared_data_wrapper_internal->commit());
        }

        SECTION("Update")
        {
            auto shared_data_wrapper_internal{
                dwc.dataWrapper<SharedDataUpdater<ShareableTestData>>()};

            auto update_result = shared_data_wrapper_internal->update(
                ShareableTestData::address());

            CHECK(update_result != nullptr);
            CHECK(update_result->a == 42);
            CHECK(update_result->b == 123.33F);
            CHECK(update_result->c == "hello test");

            update_result->a = 64;
            update_result->b = 552.125F;
            update_result->c = "updated!";

            auto shared_data_wrapper_internal2{
                dwc.dataWrapper<SharedDataViewer<ShareableTestData>>()};

            auto update_result2 = shared_data_wrapper_internal2->view(
                ShareableTestData::address());

            CHECK(update_result2 != nullptr);
            CHECK(update_result2->a == 42);
            CHECK(update_result2->b == 123.33F);
            CHECK(update_result2->c == "hello test");
        }

        SECTION("Update rollback")
        {
            {
                auto shared_data_wrapper_internal{
                    dwc.dataWrapper<SharedDataUpdater<ShareableTestData>>()};

                auto update_result = shared_data_wrapper_internal->update(
                    ShareableTestData::address());

                CHECK(update_result != nullptr);
                CHECK(update_result->a == 42);
                CHECK(update_result->b == 123.33F);
                CHECK(update_result->c == "hello test");

                update_result->a = 64;
                update_result->b = 552.125F;
                update_result->c = "updated!";

                CHECK(shared_data_wrapper_internal->rollback());
                CHECK_FALSE(shared_data_wrapper_internal->rollback());
            }

            {
                auto shared_data_wrapper_internal{
                    dwc.dataWrapper<SharedDataViewer<ShareableTestData>>()};

                auto update_result = shared_data_wrapper_internal->view(
                    ShareableTestData::address());

                CHECK(update_result != nullptr);
                CHECK(update_result->a == 42);
                CHECK(update_result->b == 123.33F);
                CHECK(update_result->c == "hello test");
            }
        }
    }
}
