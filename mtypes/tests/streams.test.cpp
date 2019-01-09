#include "catch.hpp"

#include <mtypes/include/streams.hpp>
#include <mtypes/include/types.hpp>

using namespace lib;

namespace
{
    struct PODClass
    {
        int a;
        float b;
        short c;
    };
}

TEST_CASE("SerializationStreamIn", "[streams][SerializationStreamIn]")
{
	str data { "1, 2" };
	SerializationStreamIn ssi{ std::move(data) };

	int a{ 0U };
	int b{ 0U };

	ssi >> a;
	ssi >> b;
	
	CHECK(a == 1U);
	CHECK(b == 2U);
}
