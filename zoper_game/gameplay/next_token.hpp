#pragma once

#ifndef ZOOPER_NEXT_TOKEN_INCLUDE_HPP
#define ZOOPER_NEXT_TOKEN_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/time/include/timercomponent.hpp>
#include <haf/time/include/timerconnector.hpp>

namespace zoper
{
class NextToken
{
public:
    NextToken(mtps::wptr<haf::time::TimerComponent> timer_component);
    void prepareNextToken(haf::time::TimePoint const time_to_next_token);
private:
    mtps::wptr<haf::time::TimerComponent> timer_component_;
    haf::time::TimerConnectorSPtr next_token_timer;
};
}  // namespace zoper

#endif
