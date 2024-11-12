#ifndef ZOPER_HIGHSCORESDATA_INCLUDE_HPP
#define ZOPER_HIGHSCORESDATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/array.hpp>
#include <facil_math/include/rect.hpp>
#include <haf/include/data/ifullserializable.hpp>

namespace zoper
{

constexpr htps::fast_u16 NumHighScore = 10U;

using Score = htps::size_type;

struct HighScore
{
    htps::str name{};
    Score score{0U};
};

inline const mcs::Object& operator>>(const mcs::Object& obj,
                                      HighScore& high_score_data)
{
    high_score_data.name  = obj["name"].as<htps::str>();
    high_score_data.score = obj["score"].as<Score>();
    return obj;
}

inline mcs::Object& operator<<(mcs::Object& obj,
                                const HighScore& high_score_data)
{
    obj.set("name", high_score_data.name);
    obj.set("score", high_score_data.score);
    return obj;
}

class HighScoresData : public haf::data::IFullSerializable
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
        return high_score_list_[index];
    }
    const HighScoresList& highScoresList() const noexcept
    {
        return high_score_list_;
    }

    friend mcs::Object& operator<<(mcs::Object& obj,
                                    const HighScoresData& high_scores_data);
    friend const mcs::Object& operator>>(const mcs::Object& obj,
                                          HighScoresData& high_scores_data);

    bool serialize(mcs::Object& obj) const override
    {
        obj << *this;
        return true;
    }

    bool deserialize(mcs::Object const& obj) override
    {
        obj >> *this;
        return true;
    }

private:
    HighScoresList high_score_list_;
};

inline const mcs::Object& operator>>(const mcs::Object& obj,
                                      HighScoresData& high_scores_data)
{
    if (const auto obj_high_scores_data = obj["high_scores"];
        obj_high_scores_data.isObject())
    {
        obj_high_scores_data.getObject() >> high_scores_data.high_score_list_;
    }
    return obj;
}

inline mcs::Object& operator<<(mcs::Object& obj,
                                const HighScoresData& high_scores_data)
{
    obj.set("high_scores", high_scores_data.high_score_list_);
    return obj;
}

}  // namespace zoper

#endif
