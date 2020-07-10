#pragma once

#ifndef ZOPER_HIGHSCORESDATA_INCLUDE_HPP
#define ZOPER_HIGHSCORESDATA_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/array.hpp>
#include <mtypes/include/object.hpp>

namespace zoper
{

constexpr mtps::size_type NumHighScore = 10;
using Score = mtps::size_type;

struct HighScore
{
    mtps::str name{};
    Score score{0U};
};

inline const mtps::Object &operator>>(const mtps::Object &obj, HighScore &high_score_data)
{
    high_score_data.name = obj["name"].as<mtps::str>();
    high_score_data.score = obj["score"].as<Score>();
    return obj;
}

inline mtps::Object &operator<<(mtps::Object &obj, const HighScore &high_score_data)
{
    obj.set("name", high_score_data.name);
    obj.set("score", high_score_data.score);
    return obj;
}

class HighScoresData
{
public:
    using HighScoresList = mtps::array<HighScore, NumHighScore>;
    HighScoresData();
    bool positionForScore(const Score score, mtps::size_type &positionInTable);
    bool tryInsertHighScore(const Score score, mtps::size_type &positionInTable);
    void setHighScoreName(const mtps::size_type positionInTable, const mtps::str &nName);
    const HighScore &operator[](const mtps::size_type index) const { return m_highScoreList[index]; }
    const HighScoresList &highScoresList() const noexcept { return m_highScoreList; }

    friend mtps::Object &operator<<(mtps::Object &obj, const HighScoresData &high_scores_data);
    friend const mtps::Object &operator>>(const mtps::Object &obj, HighScoresData &high_scores_data);
private:
    HighScoresList m_highScoreList;
};

inline const mtps::Object &operator>>(const mtps::Object &obj, HighScoresData &high_scores_data)
{
    if (const auto obj_high_scores_data = obj["high_scores"]; obj_high_scores_data.isObject())
    {
        obj_high_scores_data.getObject() >> high_scores_data.m_highScoreList;
    }
    return obj;
}

inline mtps::Object &operator<<(mtps::Object &obj, const HighScoresData &high_scores_data)
{
    obj.set("high_scores", high_scores_data.m_highScoreList);
    return obj;
}

} // namespace zoper

#endif
