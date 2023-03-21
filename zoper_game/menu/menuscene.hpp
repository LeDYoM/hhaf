#ifndef ZOPER_MENUSCENE_INCLUDE_HPP
#define ZOPER_MENUSCENE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/events/connection.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/scene/scene.hpp>

#include "../scene_names.hpp"

namespace zoper
{
class MenuScene final : public haf::scene::Scene
{
public:
    MenuScene();
    ~MenuScene() override;

    static constexpr char StaticTypeName[] = MENU_SCENE_NAME;

    using BaseClass = haf::scene::Scene;

    htps::str nextSceneName() override;
    void onCreated() override;
};
}  // namespace zoper

#endif
