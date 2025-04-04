#ifndef ZOPER_MENUSCENE_INCLUDE_HPP
#define ZOPER_MENUSCENE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/events/connection.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/scene_components/scene_component.hpp>
#include <haf/include/component/component.hpp>

#include "../scene_names.hpp"

namespace zoper
{
class Menu final : public haf::scene::SceneComponent
{
    using Base = haf::scene::SceneComponent;
public:
    static constexpr char StaticTypeName[] = MENU_SCENE_NAME;

    htps::str nextSceneName();
    void onAttached() override;
};
}  // namespace zoper

#endif
