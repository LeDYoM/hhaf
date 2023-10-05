#include "next_token.hpp"
#include <hlog/include/hlog.hpp>

using namespace htps;
using namespace haf::time;

namespace zoper
{
NextToken::NextToken(wptr<TimerComponent> timer_component) :
    timer_component_{htps::move(timer_component)}
{}

void NextToken::prepareNextToken(function<htps::size_type()> nextTokenTime,
                                 function<void()> nextTokenAction)
{
    time_point_getter_ = nextTokenTime;
    action_            = nextTokenAction;

    prepareNextTokenImpl();
}

void NextToken::prepareNextTokenImpl()
{
    timer_ = timer_component_.lock()->addTimer(
        TimerType::OneShot, TimePoint_as_miliseconds(time_point_getter_()),
        [this](TimePoint realEllapsed) {
            logger::DisplayLog::info("Elapsed between tokens: ",
                                  realEllapsed.milliseconds());
            // New token
            action_();
            prepareNextTokenImpl();
        });
}

}  // namespace zoper
