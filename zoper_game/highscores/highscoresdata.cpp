#include "highscoresdata.hpp"

#include <mc_serial/include/serializer.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;
using namespace haf;

namespace zoper
{
constexpr char hsfile[] = "hscores.txt";

HighScoresData::HighScoresData()
{
    size_type counter{10U};
    for (auto& element : high_score_list_)
    {
        element.name  = "AAA";
        element.score = counter * 100;
        --counter;
    }
}

bool HighScoresData::positionForScore(const Score score,
                                      size_type& positionInTable)
{
    for (u32 i{0U}; i < NumHighScore; ++i)
    {
        if (score > high_score_list_[i].score)
        {
            positionInTable = i;
            return true;
        }
    }
    return false;
}

void HighScoresData::setHighScoreName(const size_type positionInTable,
                                      const str& nName)
{
    LogAsserter::log_assert(positionInTable < high_score_list_.size(),
                            "Invalid index");
    high_score_list_[positionInTable].name = nName;
}

bool HighScoresData::tryInsertHighScore(const Score score,
                                        size_type& positionInTable)
{
    if (positionForScore(score, positionInTable))
    {
        high_score_list_.insert(positionInTable, {"", score});
        return true;
    }
    return false;
}
}  // namespace zoper
