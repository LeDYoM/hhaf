#include "catch.hpp"

#include <mtypes/include/streams.hpp>
#include <mtypes/include/types.hpp>

using namespace lib;

namespace
{
    struct PODClass
    {
        int a;
        float b;
        short c;
    };
}

TEST_CASE("streamIn constructors", "[streams][istreams][ostreams][constructor]")
{
    SerializationStreamIn ssi;
    SerializationStreamOut sso;

}
