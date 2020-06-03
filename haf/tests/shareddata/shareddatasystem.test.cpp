#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <shareddata/i_include/shareddatasystem.hpp>
#include <system/i_include/appservice.hpp>
#include <haf/system/include/isystemprovider.hpp>
#include <haf/shareddata/include/ishareable.hpp>

using namespace mtps;
using namespace haf;
using namespace haf::sys;
using namespace haf::shdata;

class MockSystemProvider : public ISystemProvider
{

};

class ShareableTest : public IShareable
{
public:
    ShareableTest(int const data) : data_{data} {}
    int& data() { return data_; }
    int const& data() const { return data_; }
private:
    int data_;
};

TEST_CASE("SharedDataSystem construction", "[haf][shareddatasystem]")
{
    MockSystemProvider mock_system_provider;
    SharedDataSystem sh_system{mock_system_provider};

    CHECK_FALSE(sh_system.store(nullptr));
    CHECK(sh_system.retrieve() == nullptr);
    CHECK(sh_system.isEmpty());
    CHECK_FALSE(sh_system.makeEmpty());

}

TEST_CASE("SharedDataSystem storing and retrieving", "[haf][shareddatasystem]")
{
    MockSystemProvider mock_system_provider;
    SharedDataSystem sh_system{mock_system_provider};

    uptr<ShareableTest> test_data(muptr<ShareableTest>(1));
    CHECK(test_data->data() == 1);
    CHECK(sh_system.store(std::move(test_data)));
    CHECK_FALSE(sh_system.isEmpty());
    CHECK(test_data == nullptr);

    auto test_data2 = sh_system.retrieve();
    CHECK_FALSE(test_data2 == nullptr);
    CHECK(sh_system.isEmpty());
    CHECK_FALSE(sh_system.makeEmpty());

    auto test_data3 = sh_system.retrieve();    
    CHECK(test_data3 == nullptr);
    CHECK(sh_system.isEmpty());
    CHECK_FALSE(sh_system.makeEmpty());

    CHECK(sh_system.store(std::move(test_data2)));
    CHECK_FALSE(sh_system.isEmpty());
    CHECK(test_data2 == nullptr);
    CHECK(sh_system.view() != nullptr);

}
