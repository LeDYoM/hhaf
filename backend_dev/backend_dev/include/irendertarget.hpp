#ifndef HAF_BACKEND_RENDER_TARGET_INCLUDE_HPP
#define HAF_BACKEND_RENDER_TARGET_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/span.hpp>

#include "iresourceinfo.hpp"

namespace haf::backend
{
class IRenderElement;
struct CameraData;

class IRenderTarget : public IResourceInfo
{
public:
    ~IRenderTarget() override = default;

    virtual void render(
        htps::rptr<CameraData const> const camera_data,
        htps::span<IRenderElement const* const> const& render_element_span) = 0;

    virtual htps::uptr<IRenderElement> createRenderElement() = 0;
};
}  // namespace haf::backend

#endif
