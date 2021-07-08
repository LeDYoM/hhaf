#ifndef ZOPER_HIGHSCORESDATA_INCLUDE_HPP
#define ZOPER_HIGHSCORESDATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/array.hpp>
#include <htypes/include/object.hpp>
#include <haf/include/shareddata/ishareable.hpp>

namespace zoper
{

constexpr htps::fast_u16 NumHighScore = 10U;

using Score = htps::size_type;

struct HighScore
{
    htps::str name{};
    Score score{0U};
};

inline const htps::Object& operator>>(const htps::Object& obj,
                                      HighScore& high_score_data)
{
    high_score_data.name  = obj["name"].as<htps::str>();
    high_score_data.score = obj["score"].as<Score>();
    return obj;
}

inline htps::Object& operator<<(htps::Object& obj,
                                const HighScore& high_score_data)
{
    obj.set("name", high_score_data.name);
    obj.set("score", high_score_data.score);
    return obj;
}

class HighScoresData : public haf::shdata::IShareable
{
public:
    using HighScoresList = htps::array<HighScore, NumHighScore>;
    HighScoresData();
    bool positionForScore(const Score score, htps::size_type& positionInTable);
    bool tryInsertHighScore(const Score score,
                            htps::size_type& positionInTable);
    void setHighScoreName(const htps::size_type positionInTable,
                          const htps::str& nName);
    const HighScore& operator[](const htps::size_type index) const
    {
        return m_highScoreList[index];
    }
    const HighScoresList& highScoresList() const noexcept
    {
        return m_highScoreList;
    }

    friend htps::Object& operator<<(htps::Object& obj,
                                    const HighScoresData& high_scores_data);
    friend const htps::Object& operator>>(const htps::Object& obj,
                                          HighScoresData& high_scores_data);

    bool serialize(htps::Object& obj) const override
    {
        obj << *this;
        return true;
    }

    bool deserialize(htps::Object const& obj) override
    {
        obj >> *this;
        return true;
    }

private:
    HighScoresList m_highScoreList;
};

inline const htps::Object& operator>>(const htps::Object& obj,
                                      HighScoresData& high_scores_data)
{
    if (const auto obj_high_scores_data = obj["high_scores"];
        obj_high_scores_data.isObject())
    {
        obj_high_scores_data.getObject() >> high_scores_data.m_highScoreList;
    }
    return obj;
}

inline htps::Object& operator<<(htps::Object& obj,
                                const HighScoresData& high_scores_data)
{
    obj.set("high_scores", high_scores_data.m_highScoreList);
    return obj;
}

}  // namespace zoper

#endif
