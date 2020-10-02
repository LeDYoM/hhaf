#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <shareddata/i_include/shareddatasystem.hpp>
#include <haf/shareddata/include/shareddataviewer.hpp>
#include "include/shareable_test_data.hpp"
#include "test_utils.hpp"

using namespace mtps;
using namespace haf::shdata;

TEST_CASE("SharedDataSystemViewer::SharedDataSystemViewer",
          "[haf][shareddatasystem]")
{
    auto test_shared_data = makeTestSystem<TestSharedDataSystem>();
    haf::sys::SharedDataSystem& sh_system =
        test_shared_data->sharedDataSystem();

    ShareableTestData shareable_test_data;

    auto dwc{test_shared_data->get()};

    SECTION("View from empty")
    {
        auto shared_data_wrapper{dwc.dataWrapper<SharedDataViewer>()};
        bool const retrieve_result = shared_data_wrapper->retrieve(
            ShareableTestData::address(), shareable_test_data);

        CHECK_FALSE(retrieve_result);
    }

    SECTION("Store and view")
    {
        shareable_test_data.a = 42;
        shareable_test_data.b = 123.33F;
        shareable_test_data.c = "hello test";

        auto shared_data_wrapper{dwc.dataWrapper<SharedDataViewer>()};
        bool const store_result = shared_data_wrapper->store(
            ShareableTestData::address(), shareable_test_data);

        CHECK(store_result);

        ShareableTestData result{};

        CHECK(result.a == 0);
        CHECK(result.b == 0.0F);
        CHECK(result.c == "");

        bool const retrieve_result =
            shared_data_wrapper->view(ShareableTestData::address(), result);

        CHECK(retrieve_result);
        CHECK(result.a == 42);
        CHECK(result.b == 123.33F);
        CHECK(result.c == "hello test");
    }
}
