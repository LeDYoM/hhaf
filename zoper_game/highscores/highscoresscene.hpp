#ifndef ZOPER_HIGHSCORESSCENE_INCLUDE_HPP
#define ZOPER_HIGHSCORESSCENE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/events/connection.hpp>

#include <haf/include/scene_components/scene_component.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ittfont.hpp>

#include "../scene_names.hpp"

namespace zoper
{
class HighScoreTextController;

class HighScores final : public haf::scene::SceneComponent
{
    using Base = haf::scene::SceneComponent;
public:
    static constexpr char StaticTypeName[] = HIGHSCORES_SCENE_NAME;

    htps::str nextSceneName() override;
    void onAttached() override;

private:
    htps::sptr<HighScoreTextController> high_score_text_controller_;
    htps::sptr<haf::res::IFont> m_normal_font;
    haf::scene::Color m_normal_color;
    haf::scene::Color m_selected_color;
};
}  // namespace zoper

#endif
