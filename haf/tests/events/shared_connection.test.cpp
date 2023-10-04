#include "catch.hpp"

#include <haf/include/core/types.hpp>

#include <haf/include/events/emitter.hpp>
#include <haf/include/events/receiver.hpp>
#include <haf/include/events/connection.hpp>
#include <haf/include/core/types.hpp>

using namespace haf;
using namespace haf::core;
using namespace haf::evt;

struct StructWithEmmiter
{
    emitter<s32> m_emitter;
    s32 m_data{0};
};

struct StructToReceive
{
    void receive(s32 const data) { m_data = data; }
    s32 m_data{0};
    ireceiver m_receiver;

    void connectTo(sptr<StructWithEmmiter> s_emitter)
    {
        m_receiver.shared_connect(
            s_emitter, s_emitter->m_emitter,
            make_function(this, &StructToReceive::receive));
    }
};

TEST_CASE("emitter_to_shared", "[emitter][connection]")
{
    auto test_emmiter{msptr<StructWithEmmiter>()};
    StructToReceive receiver{};

    receiver.connectTo(test_emmiter);
    CHECK(0 == receiver.m_data);
    CHECK(0 == test_emmiter->m_data);

    test_emmiter->m_emitter(-5);
    CHECK(-5 == receiver.m_data);
}
