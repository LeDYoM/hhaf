#ifndef ZOPER_HIGHSCORESSCENE_INCLUDE_HPP
#define ZOPER_HIGHSCORESSCENE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/connection.hpp>

#include <haf/include/scene/scene.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ittfont.hpp>

#include "../scene_names.hpp"

namespace zoper
{
class HighScoreTextController;

class HighScoresScene final : public haf::scene::Scene
{
public:
    HighScoresScene();
    ~HighScoresScene() override;

    static constexpr char StaticTypeName[] = HIGHSCORES_SCENE_NAME;

    htps::str nextSceneName() override;
    void onCreated() override;

private:
    using BaseClass = haf::scene::Scene;

    htps::sptr<HighScoreTextController> m_highScoreTextController;
    htps::sptr<haf::res::IFont> m_normalFont;
    haf::scene::Color m_normalColor;
    haf::scene::Color m_selectedColor;
};
} // namespace zoper

#endif
