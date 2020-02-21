#pragma once

#ifdef USE_DEBUG_ACTIONS

#ifndef ZOPER_DEBUG_ACTIONS_INCLUDE_HPP
#define ZOPER_DEBUG_ACTIONS_INCLUDE_HPP

#include <lib/input/include/virtual_input_component.hpp>

namespace zoper
{
class GameScene;

class DebugActions : public lib::input::VirtualInputComponent
{
private:
    using BaseClass = lib::scene::IComponent;

    void onKeyPressed(const lib::Key& key) override;
    void onKeyReleased(const lib::Key& key) override;

    GameScene* const gameScene();
public:
};
} // namespace zoper

#endif

#endif