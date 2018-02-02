#include "catch.hpp"

#include <mtypes/include/dicty.hpp>

using namespace lib::dicty;

TEST_CASE("dicty test1", "[dicty]")
{
    BasicDictionary bdictionary{ {"key1", "value1"} };
    CHECK(bdictionary.data() == BasicDictionary::content{ BasicDictionary::element("key1", "value1")});
    CHECK_FALSE(bdictionary.add("key1", "asd"));
}
