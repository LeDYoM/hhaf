#include "scoreutils.hpp"
#include "levelproperties.hpp"

#include <lib/include/liblog.hpp>

using namespace lib;
using namespace mtps;

namespace zoper
{

ScoreIncrementer::ScoreIncrementer(sptr<LevelProperties> level_properties)
    : hits_{0U}, level_properties_{std::move(level_properties)}
{
}

ScoreIncrementer::~ScoreIncrementer()
{
    for (size_type i{0U}; i < hits_; ++i)
    {
        DisplayLog::info("In a row: ", i);

        // Increase the score accordingly
        const auto score{(i + 1U) * level_properties_->baseScore()};
        level_properties_->increaseScore(score);

        // Inform that a token has been consumed
        level_properties_->tokenConsumed();
    }
    DisplayLog::info("Number of tokens in a row: ", hits_);
}

void ScoreIncrementer::addHit()
{
    ++hits_;
}

} // namespace zoper
