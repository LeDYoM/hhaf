#ifndef HAF_ZOPERPROGRAMCONTROLLER_HPP
#define HAF_ZOPERPROGRAMCONTROLLER_HPP

#include <hosted_app/include/iapp.hpp>
#include <htypes/include/types.hpp>

namespace zoper
{
class ZoperProgramController final : public haf::IApp
{
public:
    void onInit(haf::scene::AppInitializer& app_initializer) override;
    void onFinish(haf::scene::AppFinisher& app_finisher) override;

    htps::u16 getVersion() const noexcept override;
    htps::u16 getSubVersion() const noexcept override;
    htps::u16 getPatch() const noexcept override;
    htps::u16 getTweak() const noexcept override;
    htps::str getName() const noexcept override;

private:
    void configureScenes(haf::scene::AppInitializer& app_initializer);
};
}  // namespace zoper

#endif
