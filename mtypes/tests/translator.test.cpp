#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/streamin.hpp>
#include <mtypes/include/translator.hpp>

using namespace lib;

TEST_CASE("Scaner", "[streams][SerializationStreamIn][translator]")
{
	SerializationStreamIn ssi(string_vector{
		"{",
		"id : 'This is a string'"
		"}"
		});

	Scaner scanner(ssi);
	auto tokens = scanner.scan();

//	CHECK(tokens.size() == 5U);

}
