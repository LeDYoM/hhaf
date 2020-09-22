#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <shareddata/i_include/shareddatasystem.hpp>
#include <haf/shareddata/include/address.hpp>
#include <system/i_include/systembase.hpp>
#include <system/i_include/systemprovider.hpp>
#include "shareable_test_data.hpp"
#include "test_utils.hpp"

using namespace mtps;
using namespace haf;
using namespace haf::sys;
using namespace haf::shdata;

TEST_CASE("SharedDataSystem", "[haf][shareddatasystem][Object][Address]")
{
    auto test_shared_data = makeTestSystem<TestSharedDataSystem>();
    haf::sys::SharedDataSystem& sh_system =
        test_shared_data->sharedDataSystem();

    CHECK(sh_system.isEmpty());
    CHECK_FALSE(sh_system.makeEmpty());

    SECTION("Simple Store and Retrieve")
    {
        ShareableTestData test_store_data;
        test_store_data.a = 2;
        test_store_data.b = 3.14F;
        test_store_data.c = "testing";

        sh_system.store(Address(""), test_store_data);

        {
            ShareableTestData test_store_data_result;
            bool const result =
                sh_system.retrieve(Address(""), test_store_data_result);

            CHECK(result);
            CHECK(test_store_data_result.a == 2);
            CHECK(test_store_data_result.b == 3.14F);
            CHECK(test_store_data_result.c == "testing");
        }

        {
            ShareableTestData test_store_data_result;
            bool const result =
                sh_system.retrieve(Address(""), test_store_data_result);

            CHECK(result);
            CHECK(test_store_data_result.a == 2);
            CHECK(test_store_data_result.b == 3.14F);
            CHECK(test_store_data_result.c == "testing");
        }

        SECTION("Update")
        {
            ShareableTestData test_store_data_other;
            test_store_data_other.a = 42;
            test_store_data_other.b = 65.315F;
            test_store_data_other.c = "updating_testing";

            sh_system.store(Address(""), test_store_data_other);

            {
                ShareableTestData test_store_data_result;
                bool const result =
                    sh_system.retrieve(Address(""), test_store_data_result);

                CHECK(result);
                CHECK(test_store_data_result.a == 42);
                CHECK(test_store_data_result.b == 65.315F);
                CHECK(test_store_data_result.c == "updating_testing");
            }

            {
                ShareableTestData test_store_data_result;
                bool const result =
                    sh_system.retrieve(Address(""), test_store_data_result);

                CHECK(result);
                CHECK(test_store_data_result.a == 42);
                CHECK(test_store_data_result.b == 65.315F);
                CHECK(test_store_data_result.c == "updating_testing");
            }

            SECTION("makeEmpty()")
            {
                CHECK(sh_system.makeEmpty());

                ShareableTestData test_store_data_result;
                bool const result =
                    sh_system.retrieve(Address("a/"), test_store_data_result);

                CHECK_FALSE(result);
                CHECK_FALSE(sh_system.makeEmpty());
            }
        }
    }

    SECTION("Simple Store and Retrieve with address")
    {
        static constexpr char TAddrStr[] = "abc/def/";
        ShareableTestData test_store_data;
        test_store_data.a = 2;
        test_store_data.b = 3.14F;
        test_store_data.c = "testing";

        sh_system.store(Address(TAddrStr), test_store_data);

        {
            ShareableTestData test_store_data_result;
            bool const result =
                sh_system.retrieve(Address(TAddrStr), test_store_data_result);

            CHECK(result);
            CHECK(test_store_data_result.a == 2);
            CHECK(test_store_data_result.b == 3.14F);
            CHECK(test_store_data_result.c == "testing");
        }

        {
            ShareableTestData test_store_data_result;
            bool const result =
                sh_system.retrieve(Address(TAddrStr), test_store_data_result);

            CHECK(result);
            CHECK(test_store_data_result.a == 2);
            CHECK(test_store_data_result.b == 3.14F);
            CHECK(test_store_data_result.c == "testing");
        }

        SECTION("Update")
        {
            ShareableTestData test_store_data_other;
            test_store_data_other.a = 42;
            test_store_data_other.b = 65.315F;
            test_store_data_other.c = "updating_testing";

            sh_system.store(Address(TAddrStr), test_store_data_other);

            {
                ShareableTestData test_store_data_result;
                bool const result =
                    sh_system.retrieve(Address(TAddrStr), test_store_data_result);

                CHECK(result);
                CHECK(test_store_data_result.a == 42);
                CHECK(test_store_data_result.b == 65.315F);
                CHECK(test_store_data_result.c == "updating_testing");
            }

            {
                ShareableTestData test_store_data_result;
                bool const result =
                    sh_system.retrieve(Address(TAddrStr), test_store_data_result);

                CHECK(result);
                CHECK(test_store_data_result.a == 42);
                CHECK(test_store_data_result.b == 65.315F);
                CHECK(test_store_data_result.c == "updating_testing");
            }

            SECTION("makeEmpty()")
            {
                CHECK(sh_system.makeEmpty());

                ShareableTestData test_store_data_result;
                bool const result =
                    sh_system.retrieve(Address("a/"), test_store_data_result);

                CHECK_FALSE(result);
                CHECK_FALSE(sh_system.makeEmpty());
            }
        }
    }
}
