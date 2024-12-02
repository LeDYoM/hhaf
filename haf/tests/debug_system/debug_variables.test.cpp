#include "catch_include.hpp"

#include <htypes/include/types.hpp>
#include <haf/include/debug_system/debug_variable.hpp>
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
    DebugVariableHandle handle{-1};

    debug_variables.getVariable(handle, "TestDebugVariable_0");
    CHECK(handle != -1);
    CHECK(debug_variables.size() == 1U);
    CHECK_FALSE(debug_variables.empty());

    SECTION("Load existing variable")
    {
        DebugVariable value{10};
        CHECK(debug_variables.getVariableValue(handle, value));
        CHECK(value.value() == 0);
    }

    SECTION("Load unexisting variable")
    {
        DebugVariable value{10};
        DebugVariableHandle handle2{-1};
        CHECK_FALSE(debug_variables.getVariableValue(handle2, value));
    }
}

TEST_CASE("DebugVariables::DebugVariables::incrementVariable")
{
    DebugVariables debug_variables;
    DebugVariableHandle handle{-1};

    debug_variables.getVariable(handle, "TestDebugVariable_0");
    CHECK(handle != -1);
    CHECK(debug_variables.size() == 1U);
    CHECK_FALSE(debug_variables.empty());

    DebugVariable value{10};
    CHECK(debug_variables.getVariableValue(handle, value));
    CHECK(value.value() == 0);

    SECTION("Increment positive")
    {
        DebugVariable::value_type value_to_increment{10};
        debug_variables.incrementVariable(handle, value_to_increment);
        DebugVariable value_get{1};
        CHECK(debug_variables.getVariableValue(handle, value_get));
        CHECK(value_get.value() == 10);
    }

    SECTION("Increment negative")
    {
        DebugVariable::value_type value_to_increment{-10};
        debug_variables.incrementVariable(handle, value_to_increment);
        DebugVariable value_get{10};
        CHECK(debug_variables.getVariableValue(handle, value_get));
        CHECK(value_get.value() == -10);
    }

    SECTION("Increment default")
    {
        debug_variables.incrementVariable(handle);
        DebugVariable value_get{10};
        CHECK(debug_variables.getVariableValue(handle, value_get));
        CHECK(value_get.value() == 1);
    }
}

TEST_CASE("DebugVariables::DebugVariables::setVariable")
{
    DebugVariables debug_variables;
    DebugVariableHandle handle{-1};

    debug_variables.getVariable(handle, "TestDebugVariable_0");
    CHECK(handle != -1);
    CHECK(debug_variables.size() == 1U);
    CHECK_FALSE(debug_variables.empty());

    DebugVariable value{10};
    CHECK(debug_variables.getVariableValue(handle, value));
    CHECK(value.value() == 0);

    SECTION("Set positive")
    {
        DebugVariable::value_type value_to_set{123};
        debug_variables.setVariable(handle, value_to_set);
        DebugVariable value_get{1};
        CHECK(debug_variables.getVariableValue(handle, value_get));
        CHECK(value_get.value() == 123);
    }

    SECTION("Set negative")
    {
        DebugVariable::value_type value_to_set{-200};
        debug_variables.setVariable(handle, value_to_set);
        DebugVariable value_get{10};
        CHECK(debug_variables.getVariableValue(handle, value_get));
        CHECK(value_get.value() == -200);
    }

    SECTION("Set default")
    {
        debug_variables.setVariable(handle);
        DebugVariable value_get{10};
        CHECK(debug_variables.getVariableValue(handle, value_get));
        CHECK(value_get.value() == 0);
    }
}
