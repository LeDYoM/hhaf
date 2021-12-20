#include "catch.hpp"

#include <htypes/include/types.hpp>
#include "shareddata/shared_data_system.hpp"
#include <haf/include/shareddata/shared_data_updater.hpp>
#include <haf/include/shareddata/shared_data_viewer.hpp>
#include "include/shareable_test_data.hpp"
#include "system_test_utils.hpp"

using namespace htps;
using namespace haf::shdata;

TEST_CASE("SharedDataSystemUpdater::SharedDataSystemUpdater",
          "[haf][shareddatasystem]")
{
    auto const test_shared_data{makeTestSystem<TestSharedDataSystem>()};

    ShareableTestData shareable_test_data;

    auto ssv{test_shared_data->getSubSystemViewer()};

    SECTION("View from empty")
    {
        auto shared_data_viewer{
            SharedDataViewer<ShareableTestData>{ssv.subSystem<ISharedData>()}};

        auto const retrieve_result{
            shared_data_viewer.view(ShareableTestData::address())};

        CHECK_FALSE(retrieve_result);

        auto shared_data_updater{
            SharedDataUpdater<ShareableTestData>{ssv.subSystem<ISharedData>()}};

        auto update_result{
            shared_data_updater.update(ShareableTestData::address())};

        CHECK_FALSE(update_result);
    }

    SECTION("Store and update")
    {
        shareable_test_data.a = 42;
        shareable_test_data.b = 123.33F;
        shareable_test_data.c = "hello test";

        auto shared_data{ssv.subSystem<ISharedData>()};
        bool const store_result{shared_data->store(ShareableTestData::address(),
                                                   shareable_test_data)};

        CHECK(store_result);

        SECTION("Update normal")
        {
            {
                auto shared_data_updater{SharedDataUpdater<ShareableTestData>{
                    ssv.subSystem<ISharedData>()}};

                auto update_result{
                    shared_data_updater.update(ShareableTestData::address())};

                CHECK(update_result != nullptr);
                CHECK(update_result->a == 42);
                CHECK(update_result->b == 123.33F);
                CHECK(update_result->c == "hello test");

                update_result->a = 64;
                update_result->b = 552.125F;
                update_result->c = "updated!";
            }

            {
                auto shared_data_viewer{SharedDataViewer<ShareableTestData>{
                    ssv.subSystem<ISharedData>()}};

                auto update_result{
                    shared_data_viewer.view(ShareableTestData::address())};

                CHECK(update_result);
                CHECK(update_result->a == 64);
                CHECK(update_result->b == 552.125F);
                CHECK(update_result->c == "updated!");
            }
        }
        SECTION("Update commit")
        {
            auto shared_data_updater{SharedDataUpdater<ShareableTestData>{
                ssv.subSystem<ISharedData>()}};

            auto update_result{
                shared_data_updater.update(ShareableTestData::address())};

            CHECK(update_result != nullptr);
            CHECK(update_result->a == 42);
            CHECK(update_result->b == 123.33F);
            CHECK(update_result->c == "hello test");

            update_result->a = 64;
            update_result->b = 552.125F;
            update_result->c = "updated!";

            CHECK(shared_data_updater.commit());
            CHECK_FALSE(shared_data_updater.commit());
        }

        SECTION("Update")
        {
            auto shared_data_updater{SharedDataUpdater<ShareableTestData>{
                ssv.subSystem<ISharedData>()}};

            auto update_result{
                shared_data_updater.update(ShareableTestData::address())};

            CHECK(update_result != nullptr);
            CHECK(update_result->a == 42);
            CHECK(update_result->b == 123.33F);
            CHECK(update_result->c == "hello test");

            update_result->a = 64;
            update_result->b = 552.125F;
            update_result->c = "updated!";

            auto shared_data_viewer{SharedDataViewer<ShareableTestData>{
                ssv.subSystem<ISharedData>()}};

            auto view_result{
                shared_data_viewer.view(ShareableTestData::address())};

            CHECK(view_result != nullptr);
            CHECK(view_result->a == 42);
            CHECK(view_result->b == 123.33F);
            CHECK(view_result->c == "hello test");
        }

        SECTION("Update rollback")
        {
            {
                auto shared_data_updater{SharedDataUpdater<ShareableTestData>{
                    ssv.subSystem<ISharedData>()}};

                auto update_result{
                    shared_data_updater.update(ShareableTestData::address())};

                CHECK(update_result != nullptr);
                CHECK(update_result->a == 42);
                CHECK(update_result->b == 123.33F);
                CHECK(update_result->c == "hello test");

                update_result->a = 64;
                update_result->b = 552.125F;
                update_result->c = "updated!";

                CHECK(shared_data_updater.rollback());
                CHECK_FALSE(shared_data_updater.rollback());
            }

            {
                auto shared_data_viewer{SharedDataViewer<ShareableTestData>{
                    ssv.subSystem<ISharedData>()}};

                auto update_result{
                    shared_data_viewer.view(ShareableTestData::address())};

                CHECK(update_result != nullptr);
                CHECK(update_result->a == 42);
                CHECK(update_result->b == 123.33F);
                CHECK(update_result->c == "hello test");
            }
        }
    }
}
