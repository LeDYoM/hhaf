#pragma once

#ifdef USE_DEBUG_ACTIONS

#ifndef ZOPER_DEBUG_ACTIONS_INCLUDE_HPP
#define ZOPER_DEBUG_ACTIONS_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/input/include/virtual_input_component.hpp>

namespace zoper
{
class GameScene;

class DebugActions : public lib::input::VirtualInputComponent
{
private:
    using BaseClass = lib::scene::IComponent;

    void onKeyPressed(const lib::input::Key& key) override;
    void onKeyReleased(const lib::input::Key& key) override;

    lib::rptr<GameScene> const gameScene();
};
} // namespace zoper

#endif

#endif