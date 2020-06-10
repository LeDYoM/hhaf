#include "catch.hpp"

#include <mtypes/include/dictionary.hpp>
#include <mtypes/include/types.hpp>

using namespace mtps;

TEST_CASE("dictionary::dictionary", "[mtypes][dictionry]")
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
