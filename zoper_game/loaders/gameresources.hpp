#pragma once

#ifndef ZOOPER_GAME_RESOURCES_INCLUDE_HPP
#define ZOOPER_GAME_RESOURCES_INCLUDE_HPP

#include <lib/resources/include/iresourceloader.hpp>

namespace zoper
{
class GameResources : public lib::IResourceLoader
{
public:
    static constexpr char ScoreFontId[] = "game_scene.scoreFont";
    void loadResources(lib::IResourceHandler &) override;
};
} // namespace zoper

#endif