#ifndef ZOOPER_GAMESCENE_PRIVATE_INCLUDE_HPP
#define ZOOPER_GAMESCENE_PRIVATE_INCLUDE_HPP

#include <htypes/include/types.hpp>

#include <haf/include/scene_components/animationcomponent.hpp>
#include <haf/include/random/randomnumberscomponent.hpp>
#include "gamescene.hpp"
#include "gamescene_state_manager.hpp"
#include "../keymapping.hpp"

namespace zoper
{
struct GameScene::GameScenePrivate
{
    htps::sptr<haf::scene::AnimationComponent> scene_animation_component_;
    htps::sptr<haf::rnd::RandomNumbersComponent> token_type_generator_;
    htps::sptr<haf::rnd::RandomNumbersComponent> token_position_generator_;
    htps::uptr<GameSceneStateManager> m_states_manager;
    htps::uptr<KeyMapping> key_mapping_;

    void createScoreIncrementPoints(haf::scene::SceneNode& main_node,
                                    const htps::vector2df& lastTokenPosition);
};
}  // namespace zoper

#endif
