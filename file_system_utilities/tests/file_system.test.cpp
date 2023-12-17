#include "catch_include.hpp"

#include <htypes/include/types.hpp>
#include <fsu/include/fsu.hpp>

using namespace htps;
using namespace fsu;

TEST_CASE("FileSystem::createNullFileSystem", "[fsu]")
{
    auto file_system{createNullFileSystem()};
    {
        CHECK(file_system.openFile("", OperationRead) == nullptr);
        CHECK(file_system.openFile("file_that_does_not_exist.not",
                                   OperationRead) == nullptr);
    }

    {
        CHECK(file_system.openFile("", OperationWrite) == nullptr);
        CHECK(file_system.openFile("file_that_does_not_exist.not",
                                   OperationWrite) == nullptr);
    }
}