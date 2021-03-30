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
