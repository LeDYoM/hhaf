#include "catch.hpp"

#include <htypes/include/vector.hpp>
#include <htypes/include/vector_view.hpp>
#include <htypes/include/types.hpp>

using namespace htps;

TEST_CASE("vector_view::vector_view", "[vector_view][vector]")
{
    vector<u32> test_vector;
    CHECK(test_vector.empty());
    CHECK(test_vector.size() == 0U);

    {
        vector_view<u32> test_vector_view{test_vector};
        CHECK(test_vector_view.size() == 0U);
        CHECK(test_vector_view.empty());
    }

    test_vector.push_back(3U);
    test_vector.push_back(345U);
    CHECK(test_vector.size() == 2U);

    {
        vector_view<u32> test_vector_view{test_vector};
        CHECK_FALSE(test_vector_view.empty());
        CHECK(test_vector_view.size() == 2U);
        CHECK(test_vector_view[0U] == 3U);
        CHECK(test_vector_view[1U] == 345U);
    }
}

TEST_CASE("vector_view modify elements", "[vector_view][vector]")
{
    vector<u32> test_vector;
    test_vector.push_back(3U);
    test_vector.push_back(345U);
    CHECK(test_vector.size() == 2U);

    vector_view<u32> test_vector_view{test_vector};
    CHECK(test_vector_view.size() == 2U);
    CHECK(test_vector_view[0U] == 3U);
    CHECK(test_vector_view[1U] == 345U);
    CHECK(test_vector[1U] == 345U);

    test_vector_view[1U] = 874U;
    CHECK(test_vector_view.size() == 2U);
    CHECK(test_vector_view[0U] == 3U);
    CHECK(test_vector_view[1U] == 874U);
    CHECK(test_vector[1U] == 874U);
}