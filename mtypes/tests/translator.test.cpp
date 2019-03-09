#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/streamin.hpp>
#include <mtypes/include/translator.hpp>

using namespace lib;

TEST_CASE("Scaner", "[streams][SerializationStreamIn][translator]")
{
	SerializationStreamIn ssi(string_vector{
		"{",
		"id : \"This is a string\"",
		"}"
		});

	Scaner scanner(ssi);
	auto tokens = scanner.scan();

	CHECK(tokens.size() == 5U);

	CHECK(tokens[0].value == "{");
	CHECK(tokens[0].token_type == TokenType::OpenObject);

	CHECK(tokens[1].value == "id");
	CHECK(tokens[1].token_type == TokenType::Str);

	CHECK(tokens[2].value == ":");
	CHECK(tokens[2].token_type == TokenType::KeyValueSeparator);

	CHECK(tokens[3].value == "\"This is a string\"");
	CHECK(tokens[3].token_type == TokenType::Str);

	CHECK(tokens[4].value == "}");
	CHECK(tokens[4].token_type == TokenType::CloseObject);
}
