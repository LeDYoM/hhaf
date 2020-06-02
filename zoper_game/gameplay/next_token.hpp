#pragma once

#ifndef ZOOPER_NEXT_TOKEN_INCLUDE_HPP
#define ZOOPER_NEXT_TOKEN_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/time/include/timercomponent.hpp>

namespace zoper
{
class NextToken
{
    haf::time::TimerConnectorSPtr next_token_timer;

};
}  // namespace zoper

#endif
