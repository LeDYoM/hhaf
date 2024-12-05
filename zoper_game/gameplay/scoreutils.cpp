#include "scoreutils.hpp"
#include "levelproperties.hpp"

#include <hlog/include/hlog.hpp>

using namespace haf;
using namespace htps;

namespace zoper
{

ScoreIncrementer::ScoreIncrementer(sptr<LevelProperties> level_properties) :
    hits_{0U}, level_properties_{htps::move(level_properties)}
{}

ScoreIncrementer::~ScoreIncrementer()
{
    for (size_type i{0U}; i < hits_; ++i)
    {
        logger::DisplayLog::info("In a row: ", i);

        // Increase the score accordingly
        const auto score{(i + 1U) * level_properties_->baseScore()};
        level_properties_->increaseScore(score);

        // Inform that a token has been consumed
        level_properties_->tokenConsumed();
    }
    logger::DisplayLog::info("Number of tokens in a row: ", hits_);
}

void ScoreIncrementer::addHit()
{
    ++hits_;
}

}  // namespace zoper
