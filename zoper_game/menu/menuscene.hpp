#pragma once

#ifndef ZOPER_MENUSCENE_INCLUDE_HPP
#define ZOPER_MENUSCENE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>
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

    mtps::str nextSceneName() override;
    void onCreated() override;

private:
    mtps::ireceiver m_receiver;
};
} // namespace zoper

#endif