#pragma once

#ifndef ZOOPER_GAME_RESOURCES_INCLUDE_HPP
#define ZOOPER_GAME_RESOURCES_INCLUDE_HPP

#include <haf/resources/include/iresourceloader.hpp>

namespace zoper
{
class GameResources : public haf::res::IResourceLoader
{
public:
    static constexpr char ScoreFontId[] = "game_scene.scoreFont";
    void loadResources(haf::res::IResourceHandler &) override;
};
} // namespace zoper

#endif