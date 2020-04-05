#pragma once

#ifndef ZOOPER_HIGHSCORES_RESOURCES_INCLUDE_HPP
#define ZOOPER_HIGHSCORES_RESOURCES_INCLUDE_HPP

#include <lib/resources/include/iresourceloader.hpp>

namespace zoper
{
class HighScoresResources : public haf::IResourceLoader
{
public:
    constexpr static char MenuFontId[] = "highScores.mainFont";

    void loadResources(haf::IResourceHandler &) override;
};
} // namespace zoper

#endif