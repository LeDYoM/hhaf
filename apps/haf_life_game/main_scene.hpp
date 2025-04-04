#ifndef HF_MAIN_SCENE_INCLUDE_HPP
#define HF_MAIN_SCENE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/component/component.hpp>

namespace hl
{
class MainScene final : public haf::component::Component
{
private:
    using BaseClass = haf::component::Component;

public:
    MainScene();
    ~MainScene() override;

    static constexpr char StaticTypeName[] = "MainScene";

    void onAttached() override;
};
}  // namespace hl

#endif
