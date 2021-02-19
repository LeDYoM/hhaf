#ifndef ZOPER_MENUSCENE_INCLUDE_HPP
#define ZOPER_MENUSCENE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/connection.hpp>
#include <haf/render/include/renderizable.hpp>
#include <haf/scene/include/scene.hpp>

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
} // namespace zoper

#endif