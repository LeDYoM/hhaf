#include "catch_include.hpp"

#include <htypes/include/types.hpp>
#include <fsu/include/fsu.hpp>
#include "test_utils/file_driver_test.hpp"
#include "test_utils/in_file_test.hpp"

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

TEST_CASE("FileSystem::createDiskFileSystem", "[fsu]")
{
    auto file_system{createDiskFileSystem()};
    {
        CHECK(file_system.openFile("", OperationRead) == nullptr);
        CHECK(file_system.openFile("file_that_does_not_exist.not",
                                   OperationRead) == nullptr);
    }
}

TEST_CASE("FileSystem::test_driver", "[fsu]")
{
    auto file_system{createNullFileSystem()};
    file_system.addFileDriver(muptr<fsu_test::FileDriverTest>());

    auto file_in{file_system.openFile("test1.txt", OperationRead)};
    CHECK(file_in != nullptr);

    SECTION("Read")
    {
        auto const data_read{file_in->readTextFile()};
        CHECK(data_read == htps::string_vector{ "abc", "abc", "abc"});
    }
}
