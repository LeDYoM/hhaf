#ifndef HAF_BACKEND_RENDER_TARGET_INCLUDE_HPP
#define HAF_BACKEND_RENDER_TARGET_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include "icamera.hpp"
#include "iresourceinfo.hpp"

namespace haf::backend
{
class IRenderElement;

class IRenderTarget : public IResourceInfo
{
public:
    ~IRenderTarget() override = default;

    virtual void initialize() = 0;

    virtual void render(
        IRenderElement const* const* render_element_begin,
        IRenderElement const* const* const render_element_end) = 0;

    virtual void updateCamera(CameraData const&) = 0;
    virtual void clear()                         = 0;
    virtual void forceCameraUpdate()             = 0;

    virtual IRenderElement* createRenderElement()              = 0;
    virtual bool destroyRenderElement(IRenderElement* element) = 0;
};
}  // namespace haf::backend

#endif
