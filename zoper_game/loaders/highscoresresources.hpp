#pragma once

#ifndef ZOOPER_HIGHSCORES_RESOURCES_INCLUDE_HPP
#define ZOOPER_HIGHSCORES_RESOURCES_INCLUDE_HPP

#include <haf/resources/include/iresourceloader.hpp>

namespace zoper
{
class HighScoresResources : public haf::res::IResourceLoader
{
public:
    constexpr static char MenuFontId[] = "highScores.mainFont";

    void loadResources(haf::res::IResourceHandler &) override;
};
} // namespace zoper

#endif