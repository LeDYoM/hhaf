#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <shareddata/i_include/shareddatasystem.hpp>
#include <haf/shareddata/include/shareddataviewer.hpp>
#include "include/shareable_test_data.hpp"
#include "system_test_utils.hpp"

using namespace mtps;
using namespace haf::shdata;

TEST_CASE("SharedDataSystemViewer::SharedDataSystemViewer",
          "[haf][shareddatasystem]")
{
    auto test_shared_data = makeTestSystem<TestSharedDataSystem>();
    ShareableTestData shareable_test_data;

    auto dwc{test_shared_data->get()};

    SECTION("View from empty")
    {
        auto shared_data_wrapper{
            dwc.dataWrapper<SharedDataViewer<ShareableTestData>>()};
        auto const retrieve_result = shared_data_wrapper->view(
            ShareableTestData::address());

        CHECK(retrieve_result == nullptr);
    }

    SECTION("Store and view")
    {
        shareable_test_data.a = 42;
        shareable_test_data.b = 123.33F;
        shareable_test_data.c = "hello test";

        auto shared_data_wrapper{
            dwc.dataWrapper<SharedDataViewer<ShareableTestData>>()};
        bool const store_result = shared_data_wrapper->store(
            ShareableTestData::address(), shareable_test_data);

        CHECK(store_result);

        auto const view_result =
            shared_data_wrapper->view(ShareableTestData::address());

        CHECK(view_result != nullptr);
        CHECK(view_result->a == 42);
        CHECK(view_result->b == 123.33F);
        CHECK(view_result->c == "hello test");
    }
}
