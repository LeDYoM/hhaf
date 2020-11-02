#pragma once

#ifndef ZOOPER_NEXT_TOKEN_INCLUDE_HPP
#define ZOOPER_NEXT_TOKEN_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <haf/time/include/timercomponent.hpp>
#include <haf/time/include/timerconnector.hpp>

namespace zoper
{
/**
 * @brief Class to manage the launch of a new token on the board
 */
class NextToken
{
public:
    NextToken(mtps::wptr<haf::time::TimerComponent> timer_component);
    void prepareNextToken(haf::time::TimePoint const time_to_next_token,
                          mtps::function<void()>);

private:
    mtps::wptr<haf::time::TimerComponent> timer_component_;
    haf::time::TimerConnectorSPtr next_token_timer;
};
}  // namespace zoper

#endif
