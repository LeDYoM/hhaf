#pragma once

#ifndef ZOPER_HIGHSCORESSCENE_INCLUDE_HPP
#define ZOPER_HIGHSCORESSCENE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>

#include <lib/scene/include/scene.hpp>
#include <lib/scene/include/renderizable.hpp>
#include <lib/resources/include/itexture.hpp>
#include <lib/resources/include/ittfont.hpp>

namespace zoper
{
class HighScoreTextController;

class HighScoresScene final : public lib::scene::Scene
{
public:
    HighScoresScene();
    ~HighScoresScene() override;

    static constexpr char StaticTypeName[] = "HighScoresScene";

    void onCreated() override;

private:
    using BaseClass = lib::scene::Scene;

    mtps::sptr<HighScoreTextController> m_highScoreTextController;
    mtps::sptr<lib::scene::IFont> m_normalFont;
    lib::scene::Color m_normalColor;
    lib::scene::Color m_selectedColor;
    mtps::ireceiver m_receiver;
};
} // namespace zoper

#endif
