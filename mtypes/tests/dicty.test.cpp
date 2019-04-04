#include "catch.hpp"

#include <mtypes/include/dicty.hpp>

using namespace lib;
using namespace lib::dicty;

TEST_CASE("Dicty basic values", "[dicty][ValueDictionary]")
{
    Object::ValueDictionary bdictionary{ {"key1", "value1"} };
    CHECK(bdictionary.data() == Object::ValueDictionary::content{ Object::ValueDictionary::element("key1", "value1") });
    CHECK_FALSE(bdictionary.add("key1", "asd", false));
}

TEST_CASE("dicty create 1", "[dicty]")
{
    Object tester{ {"subkey","subValue"} };
    Object obj{
        {"key1", "value1"},
        {"key2", "value2"}
    };

    CHECK(tester["subkey"] == "subValue");
    CHECK(obj["key1"] == "value1");
    CHECK(obj["key2"] == "value2");
    CHECK_FALSE(obj["key3"].isValid());
    CHECK_FALSE(obj["key1"]["value1"].isValid());
	CHECK(obj.empty_objects());
	CHECK_FALSE(obj.empty_values());
	CHECK_FALSE(obj.empty());
}

TEST_CASE("dicty create 2", "[dicty]")
{
	// Initialize with initializer list of objects
	Object obj
	{
		{ "key1",
			{
				{ "subkey1", "subvalue1" }
			}
		},
		{ "key2",
			{
				{ "subkey2", "subvalue2" }
			}
		},
		{ "key3",
			Object{ {"subkey1",
				Object {
					{ "subsubkey1", "subsubvalue" }
				}
			} }
		}
	};

	SECTION("Compare")
	{
		Object obj2{ obj };
		CHECK(obj == obj2);
		CHECK_FALSE(obj != obj2);

		const Object::Value v{ obj["key1"] };
		CHECK(v == obj2["key1"]);
		CHECK_FALSE(v != obj2["key1"]);
	}

	CHECK(obj["key1"]["subkey1"] == "subvalue1");
	CHECK(obj["key2"]["subkey2"] == "subvalue2");
	CHECK(obj["key3"]["subkey1"]["subsubkey1"] == "subsubvalue");
	CHECK(obj.size_objects() == 3U);
	CHECK(obj.empty_values());
	CHECK_FALSE(obj.empty_objects());
	CHECK_FALSE(obj.empty());
	CHECK(obj["key3"]["subkey1"].isObject());
}

TEST_CASE("dicty create 3", "[dicty]")
{
	// Initialize with initializer list of objects and initializer list of
	// properties.
	Object obj3
	{
		{
			{ "key1",
				{
					{ "subkey1", "subvalue1" }
				}
			},
			{ "key2",
				{
					{ "subkey2", "subvalue2" }
				}
			},
			{ "key3",
				Object{ {"subkey1",
					Object {
						{ "subsubkey1", "subsubvalue" }
					}
				} }
			}
		},
		{
			{"key4","value4"}
		}
	};

	CHECK(obj3["key1"]["subkey1"] == "subvalue1");
	CHECK(obj3["key2"]["subkey2"] == "subvalue2");
	CHECK(obj3["key3"]["subkey1"]["subsubkey1"] == "subsubvalue");
	CHECK_FALSE(obj3["key4"]["subkey2"] == "subvalue2");
	CHECK(obj3["key4"] == "value4");
	CHECK_FALSE(obj3["adf"].isValid());
	CHECK_FALSE(obj3["adf"] == "");
}

TEST_CASE("dicty create 4","[dicty]")
{
	// Initialize with initializer list of objects and initializer list of
	// properties.
	Object obj4
	{
		{
			{ "key1",
				{
					{ "subkey1", "subvalue1" }
				}
			},
			{ "key2",
				{
					{ "subkey2", "subvalue2" }
				}
			},
			{ "key3",
				Object{ { "subkey1",
					Object{
						{ "subsubkey1", "subsubvalue" }
					}
				}
			}
		}
		},
		{
			{ "key4","value4" }
		}
	};

	CHECK(obj4["key1"]["subkey1"] == "subvalue1");
	CHECK(obj4["key2"]["subkey2"] == "subvalue2");
	CHECK(obj4["key3"]["subkey1"]["subsubkey1"] == "subsubvalue");
	CHECK_FALSE(obj4["key4"]["subkey2"] == "subvalue2");
	CHECK(obj4["key4"] == "value4");
	CHECK_FALSE(obj4["adf"].isValid());
	CHECK_FALSE(obj4["adf"] == "");
}

TEST_CASE("Dicty: Read array1", "[dicty][vector]")
{
	Object obj{
		{"key_0", "value1"},
		{"key_1", "value2"}
	};

	CHECK(obj("key").size() == 2U);
	CHECK(obj("key", 0U) == "value1");
	CHECK(obj("key", 1U) == "value2");

	CHECK(obj("key")[0U] == "value1");
	CHECK(obj("key")[1U] == "value2");

	CHECK(obj["key_0"] == "value1");
	CHECK(obj["key_1"] == "value2");
	CHECK_FALSE(obj["key_2"].isValid());
}

TEST_CASE("Dicty: Read array2", "[dicty][vector]")
{
	// Initialize with initializer list of objects and initializer list of
	// properties.
	Object obj
	{
		{
			{ "key1",
				{
					{ "subkey_0", "subvalue0" },
					{ "subkey_1", "subvalue1" }
				}
			},
			{ "key2",
				{
					{ "subkey2", "subvalue2" }
				}
			},
			{ "key3",
				Object{ { "subkey1",
					Object{
						{ "subsubkey_0", "subsubvalue" }
					}
				}
			}
		}
		},
		{
			{ "key4","value4" }
		}
	};

	CHECK(obj("key").size() == 0U);
	CHECK(obj["key1"]("subkey").size() == 2U);
	CHECK(obj["key1"]("subkey", 0U) == "subvalue0");
	CHECK(obj["key1"]("subkey", 1U) == "subvalue1");
	CHECK(obj["key1"]["subkey_0"] == "subvalue0");
	CHECK(obj["key1"]["subkey_1"] == "subvalue1");
	CHECK_FALSE(obj["key1"]["subkey_2"].isValid());
	CHECK_FALSE(obj["key1"]["subkey_"].isValid());

	CHECK(obj["key3"]["subkey1"]("subsubkey").size() == 1U);
	CHECK(obj["key3"]["subkey1"]("subsubkey", 0U) == "subsubvalue");
	CHECK(obj["key3"]["subkey1"]["subsubkey_0"] == "subsubvalue");
	CHECK(obj["key3"]["subkey1"]["subsubkey_0"].isValid());
	CHECK_FALSE(obj["key3"]["subkey1"]["subsubkey_1"].isValid());
	CHECK_FALSE(obj["key3"]["subkey1"]["subsubkey"].isValid());
}

TEST_CASE("dicty copy", "[dicty]")
{
	// Initialize with initializer list of objects and initializer list of
	// properties.
	Object obj
	{
		{
			{ "key1",
				{
					{ "subkey1", "subvalue1" }
				}
			},
			{ "key2",
				{
					{ "subkey2", "subvalue2" }
				}
			},
			{ "key3",
				Object{ {"subkey1",
					Object {
						{ "subsubkey1", "subsubvalue" }
					}
				} }
			}
		},
		{
			{"key4","value4"}
		}
	};

	SECTION("Copy values")
	{
		Object obj2;

		CHECK(obj2.set("other_key1", obj["key1"]["subkey1"]));
		CHECK(obj2["other_key1"] == "subvalue1");

		CHECK(obj2.set("other_key2", obj["key2"]["subkey2"]));
		CHECK(obj2["other_key2"] == "subvalue2");

		CHECK(obj2.set("other_key3", obj["key3"]["subkey1"]["subsubkey1"]));
		CHECK(obj2["other_key3"] == "subsubvalue");

		CHECK(obj2.set("other_key4", obj["key4"]));
		CHECK(obj2["other_key4"] == "value4");

		CHECK_FALSE(obj2.set("other_invalid_key", obj["ínvalid_key"]));
		CHECK_FALSE(obj2["other_invalid_key"].isValid());

		// Ensure that the object is copied, not just linked.
		obj2.set("other_key1", "other_value");
		CHECK(obj["key1"]["subkey1"] == "subvalue1");
		CHECK(obj2["other_key1"] == "other_value");

	}

	SECTION("Copy objects")
	{
		Object obj2;

		CHECK(obj2.set("other_key1", obj["key1"]));
		CHECK(obj2["other_key1"]["subkey1"] == "subvalue1");

		CHECK(obj2.set("other_key2", obj["key2"]));
		CHECK(obj2["other_key2"]["subkey2"] == "subvalue2");

		CHECK(obj2.set("other_key3", obj["key3"]));
		CHECK(obj2["other_key3"]["subkey1"]["subsubkey1"] == "subsubvalue");
	}
}
