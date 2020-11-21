#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/object_utils.hpp>
#include <mtypes/include/object.hpp>

using namespace mtps;

TEST_CASE("Scaner basic 0", "[translator]")
{
    const str input{
        "{"
        "id : data"
        "}"
    };

    Scaner scanner{ input };
    auto tokens = scanner.scan();

    CHECK(tokens.size() == 5U);

    CHECK(tokens[0].value == "{");
    CHECK(tokens[0].token_type == TokenType::OpenObject);

    CHECK(tokens[1].value == "id");
    CHECK(tokens[1].token_type == TokenType::Str);

    CHECK(tokens[2].value == ":");
    CHECK(tokens[2].token_type == TokenType::KeyValueSeparator);

    CHECK(tokens[3].value == "data");
    CHECK(tokens[3].token_type == TokenType::Str);

    CHECK(tokens[4].value == "}");
    CHECK(tokens[4].token_type == TokenType::CloseObject);
}

TEST_CASE("Scaner basic 1", "[translator]")
{
    const str input{
        "{"
        "id : \"This is a string\""
        "}"
    };

    Scaner scanner{ input };
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

TEST_CASE("Scaner basic 2", "[translator]")
{
    const str input{
        "{"
        "id0 : \"This is a string\","
        "id1 : \"This  is    a diferent string\""
        "}"
    };

    Scaner scanner{ input };
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

TEST_CASE("Scaner One word strings", "[Object][utils]")
{
    const str input{
        "{"
        "id : abc ,"
        "id1 : def"
        "}"
    };

    Scaner scanner{ input };
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

TEST_CASE("Scaner numbers and letters", "[Object][utils]")
{
    const str input{
        "{"
        "id0 : 234.01 ,"
        "id1 : 1000 ,"
        "id2 : 5 ,"
        "id3 : A"
        "}"
    };

    Scaner scanner{ input };
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

TEST_CASE("Scaner numbers and letters with tabs and spaces", "[Object][utils][Scanner]")
{
    const str input{
        "{"
        "   id0 : 234.01 ,"
        "\tid1 : 1000 ,"
        "    id2 : 5 ,"
        "\t	    id3 : A"
        "}"
    };

    Scaner scanner{ input };
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

TEST_CASE("Scanner SyntaxError", "[Scanner]")
{
    const str input{
        "{"
        "   ids:\"abc"
        "}"
    };

    ObjectCompiler oc{ input };
    CHECK_FALSE(oc.compile());
    CHECK_FALSE(oc.errors().empty());
    CHECK(oc.errors().errors().size() == 1U);
    CHECK(oc.errors().errors()[0U].type == ErrorType::UnterminatedString);
}

////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Parser basic", "[streams][translator][Parser]")
{
    const str input{
        "{"
            "id : \"This is a string\""
        "}"
    };

    Parser parser(Scaner{ input }.scan());
    parser.parse();
    const Object& obj{ parser.innerObject() };

    CHECK(parser.errors().empty());
    CHECK(obj["id"] == "This is a string");

    SECTION("Write")
    {
        str sout;
        CHECK((sout << obj) == 
            "{"
                "id:\"This is a string\""
            "}");

        SECTION("Read and close loop")
        {
            Parser parser_write(Scaner{ sout }.scan());
            parser_write.parse();
            CHECK(parser_write.innerObject()["id"] == "This is a string");
            CHECK(parser_write.innerObject() == obj);
        }
    }
}

TEST_CASE("Parser: Object inside object", "[streams][translator][Parser]")
{
    const str input{
        "{"
        "   id_object : {"
        "       test_string : \"test_value\""
        "   }"
        "}"
    };

    Parser parser(Scaner{ input }.scan());
    parser.parse();
    const Object& obj{ parser.innerObject() };

    CHECK(parser.errors().empty());
    CHECK(obj.size_objects() == 1U);
    CHECK(obj.empty_values());
    CHECK(obj["id_object"].isObject());
    CHECK(obj["id_object"].getObject().empty_objects());
    CHECK(obj["id_object"].getObject().size_values() == 1U);
    CHECK(obj["id_object"]["test_string"].isValue());
    CHECK(obj["id_object"]["test_string"] == "test_value");

    SECTION("Write")
    {
        str sout;
        CHECK((sout << obj) == 
        "{"
        "id_object:{"
                "test_string:\"test_value\""
            "}"
        "}");

        SECTION("Read and close loop")
        {
            Parser parser_write(Scaner{ sout }.scan());
            parser_write.parse();
            const Object& obj2 = parser_write.innerObject();
            CHECK(obj2.size_objects() == 1U);
            CHECK(obj2.empty_values());
            CHECK(obj2["id_object"].isObject());
            CHECK(obj2["id_object"].getObject().empty_objects());
            CHECK(obj2["id_object"].getObject().size_values() == 1U);
            CHECK(obj2["id_object"]["test_string"].isValue());
            CHECK(obj2["id_object"]["test_string"] == "test_value");
            CHECK(obj2 == obj);
        }
    }
}

TEST_CASE("Parser: Object inside object with numerical values", "[streams][translator][Parser]")
{
    const str input{
        "{"
        "   id_object : {"
        "       test_string : \"test_value\""
        "   } ,"
        "   value_number : 4"
        "}"
    };

    Parser parser(Scaner{ input }.scan());
    parser.parse();
    const Object& obj{ parser.innerObject() };
    CHECK(parser.errors().empty());
    CHECK(obj.size_objects() == 1U);
    CHECK(obj.size_values() == 1U);
    CHECK(obj.size() == 2U);
    CHECK(obj["id_object"].isObject());
    CHECK(obj["id_object"].getObject().empty_objects());
    CHECK(obj["id_object"].getObject().size_values() == 1U);
    CHECK(obj["id_object"]["test_string"].isValue());
    CHECK(obj["id_object"]["test_string"] == "test_value");
    CHECK(obj["value_number"].isValue());
    CHECK(obj["value_number"].as<s32>() == 4);
    CHECK(obj["value_number"].as<u32>() == 4U);
    CHECK(obj["value_number"].as<s16>() == 4);
    CHECK(obj["value_number"].as<u16>() == 4U);

    SECTION("Write")
    {
        str sout;
        CHECK((sout << obj) == 
        "{"
            "id_object:{"
                "test_string:\"test_value\""
            "},"
            "value_number:4"
        "}"
        );

        SECTION("Read and close loop")
        {
            Parser parser_write(Scaner{ sout }.scan());
            parser_write.parse();
            const Object& obj2 = parser_write.innerObject();
            CHECK(obj2.size_objects() == 1U);
            CHECK(obj.size_values() == 1U);
            CHECK(obj.size() == 2U);
            CHECK(obj2["id_object"].isObject());
            CHECK(obj2["id_object"].getObject().empty_objects());
            CHECK(obj2["id_object"].getObject().size_values() == 1U);
            CHECK(obj2["id_object"]["test_string"].isValue());
            CHECK(obj2["id_object"]["test_string"] == "test_value");
            CHECK(obj2["value_number"].isValue());
            CHECK(obj2["value_number"].as<s32>() == 4);
            CHECK(obj2["value_number"].as<u32>() == 4U);
            CHECK(obj2["value_number"].as<s16>() == 4);
            CHECK(obj2["value_number"].as<u16>() == 4U);
            CHECK(obj2 == obj);
        }
    }
}

TEST_CASE("Parser list str properties", "[streams][translator][Parser]")
{
    const str input{
        "{"
        "   id : ["
        "       \"a\" , \"b\" , \"c\" ]"
        "}"
    };

    Parser parser(Scaner{ input }.scan());
    parser.parse();
    const Object& obj{ parser.innerObject() };

    CHECK(parser.errors().empty());
    CHECK(obj["id"][0U] == "a");
    CHECK(obj["id"][1U] == "b");
    CHECK(obj["id"][2U] == "c");

    SECTION("Write")
    {
        str sout;
        CHECK((sout << obj) == 
        "{"
            "id:"
            "["
                "\"a\",\"b\",\"c\""
            "]"
        "}"
        );

        SECTION("Read and close loop")
        {
            Parser parser_write(Scaner{ sout }.scan());
            parser_write.parse();
            const Object& obj2 = parser_write.innerObject();
            CHECK(parser_write.errors().empty());
            CHECK(obj2["id"][0U] == "a");
            CHECK(obj2["id"][1U] == "b");
            CHECK(obj2["id"][2U] == "c");
            CHECK(obj2 == obj);
        }
    }
}

TEST_CASE("Parser list object properties", "[streams][translator][Parser]")
{
    const str input{
        "{"
        "	ids : ["
        "       {"
        "           name : \"pepito\","
        "           last_name : abcd"
                "} ,"
        "       {"
        "           name : \"john\","
        "           last_name : XYZZY"
        "       }"
        "	]"
        "}"
    };

    Parser parser(Scaner{ input }.scan());
    parser.parse();
    const Object& obj{ parser.innerObject() };

    CHECK(parser.errors().empty());
    CHECK(obj["ids"][0U]["name"] == "pepito");
    CHECK(obj["ids"][0U]["last_name"] == "abcd");
    CHECK(obj["ids"][1U]["name"] == "john");
    CHECK(obj["ids"][1U]["last_name"] == "XYZZY");

    SECTION("Write")
    {
        str sout;
        CHECK((sout << obj) == 
        "{"
            "ids:["
                "{"
                    "name:\"pepito\","
                    "last_name:\"abcd\""
                "},"
                "{"
                    "name:\"john\","
                    "last_name:\"XYZZY\""
                "}"
            "]"
        "}"
        );

        SECTION("Read and close loop")
        {
            Parser parser_write(Scaner{ sout }.scan());
            parser_write.parse();
            const Object& obj2 = parser_write.innerObject();
            CHECK(parser_write.errors().empty());
            CHECK(obj2["ids"][0U]["name"] == "pepito");
            CHECK(obj2["ids"][0U]["last_name"] == "abcd");
            CHECK(obj2["ids"][1U]["name"] == "john");
            CHECK(obj2["ids"][1U]["last_name"] == "XYZZY");
            CHECK(obj2 == obj);
        }
    }
}

TEST_CASE("Parser list object and values as properties", "[streams][translator][Parser]")
{
    const str input{
        "{"
        "   ids : ["
        "       {"
        "           name : \"pepito\","
        "           last_name : abcd"
        "       } ,"
        "       \"name\""
        "   ]"
        "}"
    };

    Parser parser(Scaner{ input }.scan());
    parser.parse();
    const Object& obj{ parser.innerObject() };

    CHECK(parser.errors().empty());
    CHECK(obj["ids"][0U]["name"] == "pepito");
    CHECK(obj["ids"][0U]["last_name"] == "abcd");
    CHECK(obj["ids"][1U] == "name");

    SECTION("Write")
    {
        str sout;
        CHECK((sout << obj) == 
        "{"
            "ids:["
                "{"
                    "name:\"pepito\","
                    "last_name:\"abcd\""
                "},"
                "\"name\""
            "]"
        "}"
        );

        SECTION("Read and close loop")
        {
            Parser parser_write(Scaner{ sout }.scan());
            parser_write.parse();
            const Object& obj2 = parser_write.innerObject();
            CHECK(parser_write.errors().empty());
            CHECK(obj2["ids"][0U]["name"] == "pepito");
            CHECK(obj2["ids"][0U]["last_name"] == "abcd");
            CHECK(obj2["ids"][1U] == "name");
            CHECK(obj2 == obj);
        }
    }
}

TEST_CASE("Parser list of lists object and values as properties", "[streams][translator][Parser]")
{
    const str input{
        "{"
        "   ids : ["
        "       [ {"
        "           name : \"pepito\","
        "           last_name : abcd"
        "       } ] ,"
        "       [ {"
        "           name : \"john\","
        "           last_name : XYZZY"
        "       } ]"
        "   ]"
        "}"
    };

    Parser parser(Scaner{ input }.scan());
    parser.parse();
    const Object& obj{ parser.innerObject() };

    CHECK(parser.errors().empty());
    CHECK(obj["ids"][0U][0U]["name"] == "pepito");
    CHECK(obj["ids"][0U][0U]["last_name"] == "abcd");
    CHECK(obj["ids"][1U][0U]["name"] == "john");
    CHECK(obj["ids"][1U][0U]["last_name"] == "XYZZY");

    SECTION("Write")
    {
        str sout;
        CHECK((sout << obj) == 
        "{"
            "ids:["
                "[{"
                    "name:\"pepito\","
                    "last_name:\"abcd\""
                "}],"
                "[{"
                    "name:\"john\","
                    "last_name:\"XYZZY\""
                "}]"
            "]"
        "}"
        );

        SECTION("Read and close loop")
        {
            Parser parser_write(Scaner{ sout }.scan());
            parser_write.parse();
            const Object& obj2 = parser_write.innerObject();
            CHECK(parser_write.errors().empty());
            CHECK(obj2["ids"][0U][0U]["name"] == "pepito");
            CHECK(obj2["ids"][0U][0U]["last_name"] == "abcd");
            CHECK(obj2["ids"][1U][0U]["name"] == "john");
            CHECK(obj2["ids"][1U][0U]["last_name"] == "XYZZY");
            CHECK(obj2 == obj);
        }
    }
}

TEST_CASE("Parser list of lists object and values as properties with new sintax", "[streams][translator][Parser]")
{
    const str input{
        "{"
        "   ids:["
        "       [{"
        "           name:\"pepito\","
        "           last_name:abcd"
        "       }],"
        "       [{"
        "           name:\"john\","
        "           last_name:XYZZY"
        "       }]"
        "   ]"
        "}"
    };

    Parser parser(Scaner{ input }.scan());
    parser.parse();
    const Object& obj{ parser.innerObject() };

    CHECK(parser.errors().empty());
    CHECK(obj["ids"][0U][0U]["name"] == "pepito");
    CHECK(obj["ids"][0U][0U]["last_name"] == "abcd");
    CHECK(obj["ids"][1U][0U]["name"] == "john");
    CHECK(obj["ids"][1U][0U]["last_name"] == "XYZZY");

    SECTION("Write")
    {
        str sout;
        CHECK((sout << obj) == 
        "{"
            "ids:["
                "[{"
                    "name:\"pepito\","
                    "last_name:\"abcd\""
                "}],"
                "[{"
                    "name:\"john\","
                    "last_name:\"XYZZY\""
                "}]"
            "]"
        "}"
        );

        SECTION("Read and close loop")
        {
            Parser parser_write(Scaner{ sout }.scan());
            parser_write.parse();
            const Object& obj2 = parser_write.innerObject();
            CHECK(parser_write.errors().empty());
            CHECK(obj2["ids"][0U][0U]["name"] == "pepito");
            CHECK(obj2["ids"][0U][0U]["last_name"] == "abcd");
            CHECK(obj2["ids"][1U][0U]["name"] == "john");
            CHECK(obj2["ids"][1U][0U]["last_name"] == "XYZZY");
            CHECK(obj2 == obj);
        }
    }
}

TEST_CASE("Simple list", "[streams][translator][Parser]")
{
    const str input{
        "{"
        "	ids:[a,b,c,d,e]"
        "}"
    };

    Parser parser(Scaner{ input }.scan());
    parser.parse();
    const Object& obj{ parser.innerObject() };

    CHECK(parser.errors().empty());
    CHECK(obj["ids"][0U] == "a");
    CHECK(obj["ids"][1U] == "b");
    CHECK(obj["ids"][2U] == "c");
    CHECK(obj["ids"][3U] == "d");
    CHECK(obj["ids"][4U] == "e");

    SECTION("Write")
    {
        str sout;
        CHECK((sout << obj) == 
        "{"
            "ids:[\"a\",\"b\",\"c\",\"d\",\"e\"]"
        "}"
        );

        SECTION("Read and close loop")
        {
            Parser parser_write(Scaner{ sout }.scan());
            parser_write.parse();
            const Object& obj2 = parser_write.innerObject();
            CHECK(parser_write.errors().empty());
            CHECK(obj2["ids"][0U] == "a");
            CHECK(obj2["ids"][1U] == "b");
            CHECK(obj2["ids"][2U] == "c");
            CHECK(obj2["ids"][3U] == "d");
            CHECK(obj2["ids"][4U] == "e");
            CHECK(obj2 == obj);
        }
    }
}

TEST_CASE("Simple list with numbers", "[streams][translator][Parser]")
{
    const str input{
        "{"
        "	ids:[a,1,3.2,-5,-50.45]"
        "}"
    };

    Parser parser(Scaner{ input }.scan());
    parser.parse();
    const Object& obj{ parser.innerObject() };

    CHECK(parser.errors().empty());
    CHECK(obj["ids"][0U] == "a");
    CHECK(obj["ids"][1U].as<s32>() == 1);
    CHECK(obj["ids"][2U].as<f32>() == 3.2F);
    CHECK(obj["ids"][3U].as<s32>() == -5);
    CHECK(obj["ids"][4U].as<f32>() == -50.45F);

    SECTION("Write")
    {
        str sout;
        CHECK((sout << obj) == 
        "{"
            "ids:[\"a\",1,3.2,-5,-50.45]"
        "}"
        );

        SECTION("Read and close loop")
        {
            Parser parser_write(Scaner{ sout }.scan());
            parser_write.parse();
            const Object& obj2 = parser_write.innerObject();
            CHECK(parser_write.errors().empty());
            CHECK(obj2["ids"][1U].as<s32>() == 1);
            CHECK(obj2["ids"][2U].as<f32>() == 3.2F);
            CHECK(obj2["ids"][3U].as<s32>() == -5);
            CHECK(obj2["ids"][4U].as<f32>() == -50.45F);
            CHECK(obj2 == obj);
        }
    }
}
