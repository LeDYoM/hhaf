#pragma once

#ifndef ZOPER_MENUSCENE_INCLUDE_HPP
#define ZOPER_MENUSCENE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>
#include <lib/scene/include/renderizable.hpp>
#include <lib/scene/include/scene.hpp>

namespace zoper
{
using namespace lib;
class MenuScene final : public scene::Scene
{
public:
    MenuScene();
    ~MenuScene() override;

    static constexpr char StaticTypeName[] = "MenuScene";

    using BaseClass = scene::Scene;

    virtual void onCreated() override;

private:
    ireceiver m_receiver;
};
} // namespace zoper

#endif