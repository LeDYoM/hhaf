#ifndef ZOOPER_NEXT_TOKEN_INCLUDE_HPP
#define ZOOPER_NEXT_TOKEN_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/time/timercomponent.hpp>
#include <haf/include/time/timerconnector.hpp>

namespace zoper
{
/**
 * @brief Class to manage the launch of a new token on the board
 */
class NextToken
{
public:
    NextToken(haf::types::wptr<haf::time::TimerComponent> timer_component);
    void prepareNextToken(haf::function<htps::size_type()> nextTokenTime,
                          haf::function<void()> nextTokenAction);

private:
    void prepareNextTokenImpl();

    htps::wptr<haf::time::TimerComponent> timer_component_;
    haf::time::TimerConnectorSPtr timer_;
    haf::function<void()> action_;
    haf::function<htps::size_type()> time_point_getter_;
};
}  // namespace zoper

#endif
