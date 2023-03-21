#ifndef ZOPER_HIGHSCORESSCENE_INCLUDE_HPP
#define ZOPER_HIGHSCORESSCENE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/events/connection.hpp>

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

    htps::sptr<HighScoreTextController> high_score_text_controller_;
    htps::sptr<haf::res::IFont> normal_font_;
    haf::scene::Color normal_color_;
    haf::scene::Color selected_color_;
};
}  // namespace zoper

#endif
