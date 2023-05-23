HTPS_PRAGMA_ONCE
#ifndef HAF_SYS_SYSTEM_RENDERSYSTEM_INCLUDE_HPP
#define HAF_SYS_SYSTEM_RENDERSYSTEM_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include "system/system_base.hpp"
#include <haf/include/render/shared_data_manager.hpp>

namespace haf::sys
{
class RenderTarget;

/**
 * @brief This system is intended to be the responsible of
 * priving the render data to the Backend render part.
 */
class RenderSystem final : public SystemBase
{
public:
    using SystemBase::SystemBase;
    void initialize(bool const enableDebug);

    void update();

    core::sptr<RenderTarget> const& currentRenderTarget() const;

    render::SharedDataManager& sharedDataManager() noexcept;
    render::SharedDataManager const& sharedDataManager() const noexcept;

    void beginFrame(core::vector4df const& backgroundColor);
    void endFrame();

private:
    core::sptr<RenderTarget> render_target_;
    render::SharedDataManager m_shared_data_manager;
    bool m_initialized{false};
};
}  // namespace haf::sys

#endif
