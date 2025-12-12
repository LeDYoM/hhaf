#include "catch_include.hpp"

import memmanager;

using namespace memm;

TEST_CASE("memmanager:simpleConstructor", "[memmanager]")
{
    CHECK_FALSE(isInitialized());
    CHECK(initMemManager());
    CHECK(isInitialized());
    CHECK(finishMemManager(false));
    CHECK_FALSE(isInitialized());
}
