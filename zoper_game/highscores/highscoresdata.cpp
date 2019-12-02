#include "highscoresdata.hpp"

#include <mtypes/include/serializer.hpp>
#include <lib/include/liblog.hpp>

namespace zoper
{
using namespace lib;
constexpr char hsfile[] = "hscores.txt";

HighScoresData::HighScoresData()
{
    size_type counter{10U};
    for (auto &element : m_highScoreList)
    {
        element.name = "AAA";
        element.score = counter * 100;
        --counter;
    }
}

bool HighScoresData::positionForScore(const Score score, size_type &positionInTable)
{
    for (u32 i{0U}; i < NumHighScore; ++i)
    {
        if (score > m_highScoreList[i].score)
        {
            positionInTable = i;
            return true;
        }
    }
    return false;
}

void HighScoresData::setHighScoreName(const size_type positionInTable, const str &nName)
{
    assert_release(positionInTable < m_highScoreList.size(), "Invalid index");
    m_highScoreList[positionInTable].name = nName;
}

bool HighScoresData::tryInsertHighScore(const Score score, size_type &positionInTable)
{
    if (positionForScore(score, positionInTable))
    {
        m_highScoreList.insert(positionInTable, {"", score});
        return true;
    }
    return false;
}
} // namespace zoper
