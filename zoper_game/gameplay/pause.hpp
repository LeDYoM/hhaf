#ifndef ZOOPER_GAME_PAUSE_INCLUDE_HPP
#define ZOOPER_GAME_PAUSE_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/scene_components/text.hpp>
#include <haf/include/animation/animation_component.hpp>
#include <haf/include/component/component.hpp>

namespace zoper
{
class Pause : public haf::component::Component
{
public:
    using haf::component::Component::Component;

    void onAttached() override;

    void enterPause();
    void exitPause();

private:
    htps::sptr<haf::scene::Text> m_pause_text;
    htps::sptr<haf::anim::AnimationComponent> m_animation_component;
};
}  // namespace zoper

#endif
