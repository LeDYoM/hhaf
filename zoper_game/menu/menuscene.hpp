#ifndef ZOPER_MENUSCENE_INCLUDE_HPP
#define ZOPER_MENUSCENE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/connection.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/scene/scene.hpp>
#include <haf/include/debug_system/displayvar_console.hpp>

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
private:
    htps::sptr<haf::DisplayVarConsole> m_display_var_console{nullptr};
};
}  // namespace zoper

#endif
