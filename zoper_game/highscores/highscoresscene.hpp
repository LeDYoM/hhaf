#pragma once

#ifndef ZOPER_HIGHSCORESSCENE_INCLUDE_HPP
#define ZOPER_HIGHSCORESSCENE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>

#include <lib/scene/scene.hpp>
#include <lib/scene/renderizable.hpp>
#include <lib/resources/include/texture.hpp>
#include <lib/resources/include/ttfont.hpp>

#include <lib/include/scene/iscene.hpp>

namespace zoper
{
using namespace lib;
class HighScoreTextController;

class HighScoresScene final : public scene::Scene
{
public:
    DECLARE_SCENE(HighScoresScene)

    void onCreated() override;

private:
    using BaseClass = lib::scene::Scene;

    sptr<HighScoreTextController> m_highScoreTextController;
    sptr<scene::IFont> m_normalFont;
    scene::Color m_normalColor;
    scene::Color m_selectedColor;
    ireceiver m_receiver;
};
} // namespace zoper

#endif
