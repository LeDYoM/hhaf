#include "catch.hpp"

#include <htypes/include/types.hpp>
#include "../../haf/src/debug_system/debug_variables.hpp"

using namespace htps;
using namespace haf::debug;

TEST_CASE("DebugVariables::DebugVariables")
{
    DebugVariables debug_variables;
    CHECK(debug_variables.size() == 0U);
    CHECK(debug_variables.empty());
}

TEST_CASE("DebugVariables::DebugVariables::addVariable")
{
    DebugVariables debug_variables;
    DebugVariables::DebugVariableHandle handle{-1};

    debug_variables.getVariable(handle, "TestDebugVariable_0");
    CHECK(handle != -1);
    CHECK(debug_variables.size() == 1U);
    CHECK_FALSE(debug_variables.empty());

    SECTION("Load existing variable")
    {
        DebugVariable_t value{10};
        CHECK(debug_variables.getVariableValue(handle, value));
        CHECK(value == 0);
    }

    SECTION("Load unexisting variable")
    {
        DebugVariable_t value{10};
        DebugVariables::DebugVariableHandle handle2{-1};
        CHECK_FALSE(debug_variables.getVariableValue(handle2, value));
    }
}
