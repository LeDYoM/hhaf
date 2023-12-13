#include "catch_include.hpp"

#include <htypes/include/types.hpp>
#include <fsu/include/file_system.hpp>

using namespace htps;
using namespace fsu;

TEST_CASE("FileSystem::createNullFileSystem", "[fsu]")
{
    auto file_system{createNullFileSystem()};
    CHECK(file_system.openFile("", OperationRead{}) == nullptr);
}