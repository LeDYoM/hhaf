#include "catch_include.hpp"

import memmanager;

using namespace memm;

TEST_CASE("memmanager", "[memmanager]")
{
    CHECK_FALSE(isInitialized());
    initMemManager();
}
