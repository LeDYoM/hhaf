#include "catch.hpp"

#include <mtypes/include/dicty.hpp>

using namespace lib;
using namespace lib::dicty;

TEST_CASE("basic values", "[dicty][vd]")
{
    Object::ValueDictionary bdictionary{ {"key1", "value1"} };
    CHECK(bdictionary.data() == Object::ValueDictionary::content{ Object::ValueDictionary::element("key1", "value1")});
    CHECK_FALSE(bdictionary.add("key1", "asd",false));
}

TEST_CASE("dicty create", "[dicty][vd]")
{
	Object tester{ {"subkey","subValue"} };
    Object obj{
        {"key1", "value1"},
        {"key2", "value1"}
    };

	Object obj2{
		{ "key1", Object{{
				"subkey1", "subvalue1"
			}}
		},
		{ "key2", Object{ {
				"subkey2", "subvalue2"
			} }
		},
		{ "key3", Object{ {
				Object{ {
					"subsubkey1", "subsubvalue"
				} }
			} }
		},
		Object{ {"key4", "value4"} }
	};

}
