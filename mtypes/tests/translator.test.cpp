#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/streamin.hpp>
#include <mtypes/include/translator.hpp>
#include <mtypes/include/dicty.hpp>

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

	CHECK(tokens[3].value == "This is a string");
	CHECK(tokens[3].token_type == TokenType::Str);

	CHECK(tokens[4].value == "}");
	CHECK(tokens[4].token_type == TokenType::CloseObject);
}

TEST_CASE("Scaner basic 2", "[streams][SerializationStreamIn][translator]")
{
	SerializationStreamIn ssi(string_vector{
		"{",
		"id0 : \"This is a string\",",
		"id1 : \"This  is    a diferent string\"",
		"}"
		});

	Scaner scanner(ssi);
	auto tokens = scanner.scan();

	CHECK(tokens.size() == 9U);

	CHECK(tokens[0].value == "{");
	CHECK(tokens[0].token_type == TokenType::OpenObject);

	CHECK(tokens[1].value == "id0");
	CHECK(tokens[1].token_type == TokenType::Str);

	CHECK(tokens[2].value == ":");
	CHECK(tokens[2].token_type == TokenType::KeyValueSeparator);

	CHECK(tokens[3].value == "This is a string");
	CHECK(tokens[3].token_type == TokenType::Str);

	CHECK(tokens[4].value == ",");
	CHECK(tokens[4].token_type == TokenType::ObjectSeparator);

	CHECK(tokens[5].value == "id1");
	CHECK(tokens[5].token_type == TokenType::Str);

	CHECK(tokens[6].value == ":");
	CHECK(tokens[6].token_type == TokenType::KeyValueSeparator);

	CHECK(tokens[7].value == "This  is    a diferent string");
	CHECK(tokens[7].token_type == TokenType::Str);

	CHECK(tokens[8].value == "}");
	CHECK(tokens[8].token_type == TokenType::CloseObject);
}

TEST_CASE("Scaner One word strings", "[streams][SerializationStreamIn][translator]")
{
	SerializationStreamIn ssi(string_vector{
		"{",
		"id : abc ,",
		"id1 : def",
		"}"
		});

	Scaner scanner(ssi);
	auto tokens = scanner.scan();

	CHECK(tokens.size() == 9U);

	CHECK(tokens[0].value == "{");
	CHECK(tokens[0].token_type == TokenType::OpenObject);

	CHECK(tokens[1].value == "id");
	CHECK(tokens[1].token_type == TokenType::Str);

	CHECK(tokens[2].value == ":");
	CHECK(tokens[2].token_type == TokenType::KeyValueSeparator);

	CHECK(tokens[3].value == "abc");
	CHECK(tokens[3].token_type == TokenType::Str);

	CHECK(tokens[4].value == ",");
	CHECK(tokens[4].token_type == TokenType::ObjectSeparator);

	CHECK(tokens[5].value == "id1");
	CHECK(tokens[5].token_type == TokenType::Str);

	CHECK(tokens[6].value == ":");
	CHECK(tokens[6].token_type == TokenType::KeyValueSeparator);

	CHECK(tokens[7].value == "def");
	CHECK(tokens[7].token_type == TokenType::Str);

	CHECK(tokens[8].value == "}");
	CHECK(tokens[8].token_type == TokenType::CloseObject);
}

TEST_CASE("Scaner numbers and letters", "[streams][SerializationStreamIn][translator]")
{
	SerializationStreamIn ssi(string_vector{
		"{",
		"id0 : 234.01 ,",
		"id1 : 1000 ,",
		"id2 : 5 ,",
		"id3 : A",
		"}"
		});

	Scaner scanner(ssi);
	auto tokens = scanner.scan();

	CHECK(tokens.size() == 17U);

	CHECK(tokens[0].value == "{");
	CHECK(tokens[0].token_type == TokenType::OpenObject);

	CHECK(tokens[1].value == "id0");
	CHECK(tokens[1].token_type == TokenType::Str);

	CHECK(tokens[2].value == ":");
	CHECK(tokens[2].token_type == TokenType::KeyValueSeparator);

	CHECK(tokens[3].value == "234.01");
	CHECK(tokens[3].token_type == TokenType::Float);

	CHECK(tokens[4].value == ",");
	CHECK(tokens[4].token_type == TokenType::ObjectSeparator);

	CHECK(tokens[5].value == "id1");
	CHECK(tokens[5].token_type == TokenType::Str);

	CHECK(tokens[6].value == ":");
	CHECK(tokens[6].token_type == TokenType::KeyValueSeparator);

	CHECK(tokens[7].value == "1000");
	CHECK(tokens[7].token_type == TokenType::Integer);

	CHECK(tokens[8].value == ",");
	CHECK(tokens[8].token_type == TokenType::ObjectSeparator);

	CHECK(tokens[9].value == "id2");
	CHECK(tokens[9].token_type == TokenType::Str);

	CHECK(tokens[10].value == ":");
	CHECK(tokens[10].token_type == TokenType::KeyValueSeparator);

	CHECK(tokens[11].value == "5");
	CHECK(tokens[11].token_type == TokenType::Integer);

	CHECK(tokens[12].value == ",");
	CHECK(tokens[12].token_type == TokenType::ObjectSeparator);

	CHECK(tokens[13].value == "id3");
	CHECK(tokens[13].token_type == TokenType::Str);

	CHECK(tokens[14].value == ":");
	CHECK(tokens[14].token_type == TokenType::KeyValueSeparator);

	CHECK(tokens[15].value == "A");
	CHECK(tokens[15].token_type == TokenType::Str);

	CHECK(tokens[16].value == "}");
	CHECK(tokens[16].token_type == TokenType::CloseObject);
}

TEST_CASE("Scaner numbers and letters with tabs and spaces", "[streams][SerializationStreamIn][translator][Scanner]")
{
	SerializationStreamIn ssi(string_vector{
		"{",
		"	id0 : 234.01 ,",
		"\tid1 : 1000 ,",
		"    id2 : 5 ,",
		"\t	    id3 : A",
		"}"
		});

	Scaner scanner(ssi);
	auto tokens = scanner.scan();

	CHECK(tokens.size() == 17U);

	CHECK(tokens[0].value == "{");
	CHECK(tokens[0].token_type == TokenType::OpenObject);

	CHECK(tokens[1].value == "id0");
	CHECK(tokens[1].token_type == TokenType::Str);

	CHECK(tokens[2].value == ":");
	CHECK(tokens[2].token_type == TokenType::KeyValueSeparator);

	CHECK(tokens[3].value == "234.01");
	CHECK(tokens[3].token_type == TokenType::Float);

	CHECK(tokens[4].value == ",");
	CHECK(tokens[4].token_type == TokenType::ObjectSeparator);

	CHECK(tokens[5].value == "id1");
	CHECK(tokens[5].token_type == TokenType::Str);

	CHECK(tokens[6].value == ":");
	CHECK(tokens[6].token_type == TokenType::KeyValueSeparator);

	CHECK(tokens[7].value == "1000");
	CHECK(tokens[7].token_type == TokenType::Integer);

	CHECK(tokens[8].value == ",");
	CHECK(tokens[8].token_type == TokenType::ObjectSeparator);

	CHECK(tokens[9].value == "id2");
	CHECK(tokens[9].token_type == TokenType::Str);

	CHECK(tokens[10].value == ":");
	CHECK(tokens[10].token_type == TokenType::KeyValueSeparator);

	CHECK(tokens[11].value == "5");
	CHECK(tokens[11].token_type == TokenType::Integer);

	CHECK(tokens[12].value == ",");
	CHECK(tokens[12].token_type == TokenType::ObjectSeparator);

	CHECK(tokens[13].value == "id3");
	CHECK(tokens[13].token_type == TokenType::Str);

	CHECK(tokens[14].value == ":");
	CHECK(tokens[14].token_type == TokenType::KeyValueSeparator);

	CHECK(tokens[15].value == "A");
	CHECK(tokens[15].token_type == TokenType::Str);

	CHECK(tokens[16].value == "}");
	CHECK(tokens[16].token_type == TokenType::CloseObject);
}

////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Parser basic", "[streams][SerializationStreamIn][translator][Parser]")
{
	SerializationStreamIn ssi(string_vector{
		"{",
		"id : \"This is a string\"",
		"}"
		});

	Parser parser(Scaner{ ssi }.scan());
	parser.parse();
	const dicty::Object& obj{ parser.innerObject() };

	CHECK(parser.errors().empty());
	CHECK(obj["id"] == "This is a string");
}
