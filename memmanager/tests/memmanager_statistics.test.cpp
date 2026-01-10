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

    int* a = new int;
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

    // For now, global operator new and delete cannot be overriden.
/*
    int* b = new int[2];
    {
        MemoryStatistics mg{getGlobalMemoryStatistics()};
        CHECK(mg.num_alloc == 2U);
        CHECK(mg.num_dealloc == 1U);
        CHECK(mg.bytes_alloc == sizeof(int) * 3U);
        CHECK(mg.bytes_dealloc == sizeof(int));
    }

    delete[] b;

    {
        MemoryStatistics mg{getGlobalMemoryStatistics()};
        CHECK(mg.num_alloc == 2U);
        CHECK(mg.num_dealloc == 2U);
        CHECK(mg.bytes_alloc == sizeof(int) * 3U);
        CHECK(mg.bytes_dealloc == sizeof(int) * 3U);
    }
*/
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
    int* a = new int;
    {
        MemoryStatistics mg{getGlobalMemoryStatistics()};
        CHECK(mg.num_alloc == 1U);
        CHECK(mg.num_dealloc == 0U);
        CHECK(mg.bytes_alloc == sizeof(int));
        CHECK(mg.bytes_dealloc == 0U);
    }

    pushMemoryStatisticsQueue();
    int* b = new int;
    {
        auto const* mg{getHeadMemoryStatistics()};
        CHECK(mg->num_alloc == 1U);
        CHECK(mg->num_dealloc == 0U);
        CHECK(mg->bytes_alloc == sizeof(int));
        CHECK(mg->bytes_dealloc == 0U);
    }

    {
        MemoryStatistics mg{getGlobalMemoryStatistics()};
        CHECK(mg.num_alloc == 2U);
        CHECK(mg.num_dealloc == 0U);
        CHECK(mg.bytes_alloc == sizeof(int) * 2U);
        CHECK(mg.bytes_dealloc == 0U);
    }

    delete a;

    {
        auto const* mg{getHeadMemoryStatistics()};
        CHECK(mg->num_alloc == 1U);
        CHECK(mg->num_dealloc == 1U);
        CHECK(mg->bytes_alloc == sizeof(int));
        CHECK(mg->bytes_dealloc == sizeof(int));
    }

    {
        MemoryStatistics mg{getGlobalMemoryStatistics()};
        CHECK(mg.num_alloc == 2U);
        CHECK(mg.num_dealloc == 1U);
        CHECK(mg.bytes_alloc == sizeof(int) * 2U);
        CHECK(mg.bytes_dealloc == sizeof(int));
    }

    CHECK(popMemoryStatisticsQueue());
    CHECK(canAddNode());
    delete b;

    {
        auto const* mg{getHeadMemoryStatistics()};
        CHECK(mg->num_alloc == 2U);
        CHECK(mg->num_dealloc == 2U);
        CHECK(mg->bytes_alloc == sizeof(int) * 2U);
        CHECK(mg->bytes_dealloc == sizeof(int) * 2U);
    }

    {
        MemoryStatistics mg{getGlobalMemoryStatistics()};
        CHECK(mg.num_alloc == 2U);
        CHECK(mg.num_dealloc == 2U);
        CHECK(mg.bytes_alloc == sizeof(int) * 2U);
        CHECK(mg.bytes_dealloc == sizeof(int) * 2U);
    }

    CHECK(finishMemManager(false));
}

/*
namespace
struct Simple
TEST_CASE("memmanager:heterogeneous_types", "[memmanager]")
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
*/