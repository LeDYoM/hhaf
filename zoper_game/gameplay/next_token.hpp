#ifndef ZOOPER_NEXT_TOKEN_INCLUDE_HPP
#define ZOOPER_NEXT_TOKEN_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/function.hpp>
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
    NextToken(htps::wptr<haf::time::TimerComponent> timer_component);
    void prepareNextToken(htps::function<htps::size_type()> nextTokenTime,
                          htps::function<void()> nextTokenAction);

private:
    void prepareNextTokenImpl();

    htps::wptr<haf::time::TimerComponent> timer_component_;
    haf::time::TimerConnectorSPtr timer_;
    htps::function<void()> action_;
    htps::function<htps::size_type()> time_point_getter_;
};
}  // namespace zoper

#endif
