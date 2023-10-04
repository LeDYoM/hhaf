#include "catch.hpp"

#include <haf/include/core/types.hpp>

#include <haf/include/events/emitter.hpp>
#include <haf/include/events/receiver.hpp>
#include <haf/include/events/connection.hpp>

using namespace haf;
using namespace haf::core;
using namespace haf::evt;

struct StructWithEmmiter
{
    emitter<s32> m_emitter;
    s32 data{0};
};

struct StructToReceive
{
    void receiveData(s32 const data)
    {
        m_data = data;
    }
    s32 m_data{0};
};

TEST_CASE("emitter_to_shared", "[emitter][connection]")
{
}

