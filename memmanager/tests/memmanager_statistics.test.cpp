#include "catch_include.hpp"

import memmanager;

using namespace memm;

TEST_CASE("memmanager:emptyStatistics", "[memmanager]")
{
    CHECK(initMemManager());
    CHECK(isInitialized());
    MemoryStatistics mg{getGlobalMemoryStatistics()};
    CHECK(mg.num_alloc == 0U);
    CHECK(mg.num_dealloc == 0U);
    CHECK(mg.bytes_alloc == 0U);
    CHECK(mg.bytes_dealloc == 0U);
    CHECK(finishMemManager(false));
}

TEST_CASE("memmanager:basicStatistics", "[memmanager]")
{
    CHECK(initMemManager());
    CHECK(isInitialized());
    {
        MemoryStatistics mg{getGlobalMemoryStatistics()};
        CHECK(mg.num_alloc == 0U);
        CHECK(mg.num_dealloc == 0U);
        CHECK(mg.bytes_alloc == 0U);
        CHECK(mg.bytes_dealloc == 0U);
    }

    int* a = new int[1];
    {
        MemoryStatistics mg{getGlobalMemoryStatistics()};
        CHECK(mg.num_alloc == 1U);
        CHECK(mg.num_dealloc == 0U);
        CHECK(mg.bytes_alloc == sizeof(int));
        CHECK(mg.bytes_dealloc == 0U);
    }

    delete a;

    {
        MemoryStatistics mg{getGlobalMemoryStatistics()};
        CHECK(mg.num_alloc == 1U);
        CHECK(mg.num_dealloc == 1U);
        CHECK(mg.bytes_alloc == sizeof(int));
        CHECK(mg.bytes_dealloc == sizeof(int));
    }

    CHECK(finishMemManager(false));
}

TEST_CASE("memmanager:queueStatistics", "[memmanager]")
{
    CHECK(initMemManager());
    CHECK(isInitialized());
    {
        MemoryStatistics mg{getGlobalMemoryStatistics()};
        CHECK(mg.num_alloc == 0U);
        CHECK(mg.num_dealloc == 0U);
        CHECK(mg.bytes_alloc == 0U);
        CHECK(mg.bytes_dealloc == 0U);
    }

    CHECK(canAddNode());
    int* a = new int[1];
    {
        MemoryStatistics mg{getGlobalMemoryStatistics()};
        CHECK(mg.num_alloc == 1U);
        CHECK(mg.num_dealloc == 0U);
        CHECK(mg.bytes_alloc == sizeof(int));
        CHECK(mg.bytes_dealloc == 0U);
    }

    pushMemoryStatisticsQueue();
    int* b = new int[2];
    {
        auto mh{getHeadMemoryStatistics()};
        CHECK(mg.num_alloc == 1U);
        CHECK(mg.num_dealloc == 0U);
        CHECK(mg.bytes_alloc == sizeof(int) * 2U);
        CHECK(mg.bytes_dealloc == 0U);

    }

    {
        MemoryStatistics mg{getGlobalMemoryStatistics()};
        CHECK(mg.num_alloc == 2U);
        CHECK(mg.num_dealloc == 0U);
        CHECK(mg.bytes_alloc == sizeof(int) * 3U);
        CHECK(mg.bytes_dealloc == 0U);
    }

    (void)(a);
    (void)(b);

    CHECK(finishMemManager(false));
}
