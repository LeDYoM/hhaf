#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/streamin.hpp>
#include <mtypes/include/translator.hpp>

using namespace lib;

TEST_CASE("Scaner basic", "[streams][SerializationStreamIn][translator]")
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

TEST_CASE("Scaner basic 2", "[streams][SerializationStreamIn][translator]")
{
	SerializationStreamIn ssi(string_vector{
		"{",
		"id0 : \"This is a string\"",
		"id1 : \"This  is    a diferent string\"",
		"}"
		});

	Scaner scanner(ssi);
	auto tokens = scanner.scan();

	CHECK(tokens.size() == 8U);

	CHECK(tokens[0].value == "{");
	CHECK(tokens[0].token_type == TokenType::OpenObject);

	CHECK(tokens[1].value == "id0");
	CHECK(tokens[1].token_type == TokenType::Str);

	CHECK(tokens[2].value == ":");
	CHECK(tokens[2].token_type == TokenType::KeyValueSeparator);

	CHECK(tokens[3].value == "\"This is a string\"");
	CHECK(tokens[3].token_type == TokenType::Str);

	CHECK(tokens[4].value == "id1");
	CHECK(tokens[4].token_type == TokenType::Str);

	CHECK(tokens[5].value == ":");
	CHECK(tokens[5].token_type == TokenType::KeyValueSeparator);

	CHECK(tokens[6].value == "\"This  is    a diferent string\"");
	CHECK(tokens[6].token_type == TokenType::Str);

	CHECK(tokens[7].value == "}");
	CHECK(tokens[7].token_type == TokenType::CloseObject);
}
