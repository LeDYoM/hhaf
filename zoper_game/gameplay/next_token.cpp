#include "next_token.hpp"
#include <hlog/include/hlog.hpp>

using namespace mtps;
using namespace haf;

namespace zoper
{
NextToken::NextToken(wptr<time::TimerComponent> timer_component) :
    timer_component_{std::move(timer_component)}
{}

void NextToken::prepareNextToken(function<mtps::size_type()> nextTokenTime,
                                 function<void()> nextTokenAction)
{
    time_point_getter_ = nextTokenTime;
    action_            = nextTokenAction;

    prepareNextTokenImpl();
}

void NextToken::prepareNextTokenImpl()
{
    timer_ = timer_component_.lock()->addTimer(
        time::TimerType::OneShot,
        time::TimePoint_as_miliseconds(time_point_getter_()),
        [this](time::TimePoint realEllapsed) {
            DisplayLog::info("Elapsed between tokens: ",
                             realEllapsed.milliseconds());
            // New token
            action_();
            prepareNextTokenImpl();
        });
}

}  // namespace zoper
