#include "catch.hpp"

#include <htypes/include/dictionary.hpp>
#include <htypes/include/types.hpp>

using namespace htps;

TEST_CASE("dictionary::dictionary", "[htypes][dictionry]")
{
    {
        Dictionary<int> v;
        CHECK(v.size() == 0U);
        CHECK(v.empty());
    }

    {
        Dictionary<int> v{{"ABC", 4}};

        CHECK(v.size() == 1U);
        CHECK_FALSE(v.empty());

        CHECK((*(v.find("ABC"))).second == 4);
    }
}

TEST_CASE("dictionary::find", "[htypes][dictionry]")
{
    Dictionary<int> v{{"ABC", 4}};
    CHECK(v.add("bcd", 100));
    CHECK(v.add("zxy", 3455));

    CHECK((*(v.find("bcd"))).second == 100);
    CHECK(v.find("bcde") == v.end());
    CHECK(v.find("") == v.end());
    CHECK(v.find("dfgdf") == v.end());

    CHECK(v.cfind("bcde") == v.cend());
    CHECK(v.cfind("") == v.cend());
    CHECK(v.cfind("dfgdf") == v.cend());

    CHECK(v.size() == 3U);
    CHECK_FALSE(v.empty());

    v.clear();

    CHECK(v.size() == 0U);
    CHECK(v.empty());
}

TEST_CASE("dictionary::find_checked", "[htypes][dictionry]")
{
    Dictionary<int> v{{"ABC", 4}};
    CHECK(v.add("bcd", 100));
    CHECK(v.add("zxy", 3455));

    {
        auto const result{v.find_checked("bcd")};
        CHECK(result.first == true);
        CHECK((*(result.second)).second == 100);
    }

    {
        auto const result{v.find_checked("bcde")};
        CHECK(result.first == false);
        CHECK(result.second == v.end());
    }

    {
        auto const result{v.find_checked("dfgdf")};
        CHECK(result.first == false);
        CHECK(result.second == v.end());
    }

    {
        auto const result{v.cfind_checked("bcde")};
        CHECK(result.first == false);
        CHECK(result.second == v.cend());
    }

    {
        auto const result{v.cfind_checked("dfgdf")};
        CHECK(result.first == false);
        CHECK(result.second == v.cend());
    }

    CHECK(v.size() == 3U);
    CHECK_FALSE(v.empty());

    v.clear();

    CHECK(v.size() == 0U);
    CHECK(v.empty());
}

TEST_CASE("dictionary::add no overwrite", "[htypes][dictionry]")
{
    Dictionary<int> v{{"ABC", 4}};
    CHECK(v.add("bcd", 100, false));
    CHECK(v.add("zxy", 3455, false));

    CHECK(v.size() == 3U);

    CHECK_FALSE(v.add("bcd", 300, false));
    CHECK(v.size() == 3U);
    CHECK((*(v.find("bcd"))).second == 100);
}
