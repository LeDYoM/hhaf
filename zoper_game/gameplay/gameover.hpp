#ifndef ZOPER_GAMEOVER_INCLUDE_HPP
#define ZOPER_GAMEOVER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/component/component.hpp>
#include <haf/include/scene/scene_node.hpp>

namespace zoper
{
class GameOver : public haf::component::Component
{
    using Base = haf::component::Component;

public:
    using Base::Base;

    void onAttached() override;

private:
    htps::sptr<haf::scene::SceneNode> m_game_over_rg;
};
}  // namespace zoper

#endif
