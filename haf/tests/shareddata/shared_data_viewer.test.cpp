#include "catch.hpp"

#include <htypes/include/types.hpp>
#include "shareddata/shared_data_system.hpp"
#include <haf/include/shareddata/shared_data_viewer.hpp>
#include "include/shareable_test_data.hpp"
#include "system_test_utils.hpp"

using namespace htps;
using namespace haf::shdata;
using namespace haf;
using namespace haf::test;

TEST_CASE("SharedDataSystemViewer::SharedDataSystemViewer",
          "[haf][shareddatasystem]")
{
    auto test_shared_data{makeTestSystem<TestSharedDataSystem>()};
    ShareableTestData shareable_test_data;

    auto ssv{test_shared_data->getSubSystemViewer()};

    SECTION("View from empty")
    {
        auto shared_data_viewer{
            SharedDataViewer<ShareableTestData>{ssv.subSystem<ISharedData>()}};
        auto const retrieve_result{
            shared_data_viewer.view(ShareableTestData::address())};

        CHECK(retrieve_result == nullptr);
    }

    SECTION("Store and view")
    {
        shareable_test_data.a = 42;
        shareable_test_data.b = 123.33F;
        shareable_test_data.c = "hello test";

        auto ishared_data{ssv.subSystem<ISharedData>()};
        bool const store_result = ishared_data->store(
            ShareableTestData::address(), shareable_test_data);

        CHECK(store_result);

        auto shared_data_viewer{
            SharedDataViewer<ShareableTestData>{ssv.subSystem<ISharedData>()}};
        auto const view_result{
            shared_data_viewer.view(ShareableTestData::address())};

        CHECK(view_result != nullptr);
        CHECK(view_result->a == 42);
        CHECK(view_result->b == 123.33F);
        CHECK(view_result->c == "hello test");
    }
}
