#include "catch_include.hpp"

import memmanager;

using namespace memm;

TEST_CASE("memmanager:enmptyStatistics", "[memmanager]")
{
    CHECK(initMemManager());
    CHECK(isInitialized());
    MemoryStatistics mg{getGlobalMemoryStatistics()};
    CHECK(finishMemManager(false));
}
