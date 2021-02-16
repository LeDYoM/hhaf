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
    NextToken(mtps::wptr<haf::time::TimerComponent> timer_component);
    void prepareNextToken(mtps::function<mtps::size_type()> nextTokenTime,
                          mtps::function<void()> nextTokenAction);

private:
    void prepareNextTokenImpl();

    mtps::wptr<haf::time::TimerComponent> timer_component_;
    haf::time::TimerConnectorSPtr timer_;
    mtps::function<void()> action_;
    mtps::function<mtps::size_type()> time_point_getter_;
};
}  // namespace zoper

#endif
