#include "next_token.hpp"
#include <hlog/include/hlog.hpp>

using namespace mtps;
using namespace haf;

namespace zoper
{
NextToken::NextToken(wptr<time::TimerComponent> timer_component) :
    timer_component_{std::move(timer_component)}
{}

void NextToken::prepareNextToken(time::TimePoint const time_to_next_token,
                                 mtps::function<void()> next_token_function)
{
    next_token_timer = timer_component_.lock()->addTimer(
        time::TimerType::Continuous, time_to_next_token,
        [this, next_token_function = std::move(next_token_function)](
            time::TimePoint realEllapsed) {
            DisplayLog::info("Elapsed between tokens: ",
                             realEllapsed.milliseconds());
            // New token
            next_token_function();
        });
}
}  // namespace zoper
