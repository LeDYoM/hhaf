#include "next_token.hpp"

using namespace mtps;
using namespace haf;

namespace zoper
{
NextToken::NextToken(wptr<time::TimerComponent> timer_component) :
    timer_component_{std::move(timer_component)}
{}

void NextToken::prepareNextToken(time::TimePoint const time_to_next_token)
{
    /*
        m_nextTokenTimer = scene_timer_component_->addTimer(
        time::TimerType::Continuous,
        time::TimePoint_as_miliseconds(
            level_properties_->millisBetweenTokens()),
        [this](time::TimePoint realEllapsed) {
            DisplayLog::info("Elapsed between tokens: ",
                             realEllapsed.milliseconds());
            // New token
            generateNextToken();
        });
        */
}
}  // namespace zoper
