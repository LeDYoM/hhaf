#ifndef HAF_BACKEND_RENDER_TARGET_INCLUDE_HPP
#define HAF_BACKEND_RENDER_TARGET_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>
#include <htypes/include/rect.hpp>
#include "irenderdata.hpp"
#include "iresourceinfo.hpp"

namespace haf::backend
{
class IRenderTarget : public IResourceInfo
{
public:
    ~IRenderTarget() override {}

    virtual void initialize() = 0;

    virtual void render(IRenderData const * render_data_begin,
                        IRenderData const* const render_data_end) = 0;

    virtual void setViewPort(const htps::Rectf32& nviewport) = 0;
    virtual htps::Rectf32 viewPort() const                   = 0;
    virtual void setViewRect(const htps::Rectf32& nviewRect) = 0;
    virtual htps::Rectf32 viewRect() const                   = 0;

    virtual void clear() = 0;
};
}  // namespace haf::backend

#endif
