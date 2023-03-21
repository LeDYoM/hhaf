HTPS_PRAGMA_ONCE
#ifndef HAF_SYS_SYSTEM_RENDERSYSTEM_INCLUDE_HPP
#define HAF_SYS_SYSTEM_RENDERSYSTEM_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include "system/system_base.hpp"

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

    htps::sptr<RenderTarget> const& currentRenderTarget() const;

private:
    htps::sptr<RenderTarget> render_target_;
    bool m_initialized{false};
};
}  // namespace haf::sys

#endif
