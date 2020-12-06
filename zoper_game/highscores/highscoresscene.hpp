#ifndef ZOPER_HIGHSCORESSCENE_INCLUDE_HPP
#define ZOPER_HIGHSCORESSCENE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>

#include <haf/scene/include/scene.hpp>
#include <haf/render/include/renderizable.hpp>
#include <haf/resources/include/itexture.hpp>
#include <haf/resources/include/ittfont.hpp>

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

    mtps::str nextSceneName() override;
    void onCreated() override;

private:
    using BaseClass = haf::scene::Scene;

    mtps::sptr<HighScoreTextController> m_highScoreTextController;
    mtps::sptr<haf::res::IFont> m_normalFont;
    haf::scene::Color m_normalColor;
    haf::scene::Color m_selectedColor;
    mtps::ireceiver m_receiver;
};
} // namespace zoper

#endif
