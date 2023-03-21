#include "catch.hpp"

#include <haf/include/core/types.hpp>
#include "filesystem/file_system.hpp"
#include "system_test_utils.hpp"

using namespace haf;
using namespace haf::sys;
using namespace haf::test;

TEST_CASE("FileSystem", "[haf][FileSystem][Object][Address]")
{
    auto test_file_system{makeTestSystem<TestFileSystem>()};
    FileSystem& file_system{test_file_system->system<FileSystem>()};
    (void)(file_system);
//    CHECK(file_system.addVirtualFile("test.txt", "abc\nother"));
}
