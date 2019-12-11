#pragma once

#ifndef ZOOPER_HIGHSCORES_RESOURCES_INCLUDE_HPP
#define ZOOPER_HIGHSCORES_RESOURCES_INCLUDE_HPP

#include <lib/include/resources/iresourceloader.hpp>

namespace zoper
{
class HighScoresResources : public lib::IResourceLoader
{
public:
    constexpr static char MenuFontId[] = "highScores.mainFont";

    void loadResources(lib::IResourceHandler &) override;
};
} // namespace zoper

#endif