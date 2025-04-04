#ifndef ZOPER_GAMEHUD_COMPONENT_INCLUDE_HPP
#define ZOPER_GAMEHUD_COMPONENT_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/component/component.hpp>
#include <haf/include/scene_components/table_of_text_quad.hpp>

namespace zoper
{

class GameHud final : public haf::component::Component
{
    using Base = haf::component::Component;

public:
    using Base::Base;

    void update() override;

    haf::prop::PropertyState<htps::size_type> currentLevel;
    haf::prop::PropertyState<htps::size_type> currentScore;
    haf::prop::PropertyState<htps::size_type> currentConsumedTokens;
    haf::prop::PropertyState<htps::u64> currentEllapsedTimeInSeconds;
    haf::prop::PropertyState<htps::size_type> currentStayCounter;

    void onAttached() override;

private:
    void onAllScoreElementsCreated(fmath::vector2dst const);
    void onAllGoalElementsCreated(fmath::vector2dst const);
    bool setLevel(const htps::size_type level);
    bool setScore(htps::size_type const score);
    bool setConsumedTokens(htps::size_type const consumedTokens);
    bool setEllapsedTimeInSeconds(htps::u64 const seconds);
    bool setStayCounter(htps::size_type const stayCounter);

    htps::sptr<haf::scene::TableOfTextQuad> m_score_quad;
    htps::sptr<haf::scene::TableOfTextQuad> m_goal_quad;
};
}  // namespace zoper

#endif
