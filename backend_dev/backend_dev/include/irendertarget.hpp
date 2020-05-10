#pragma once

#ifndef HAF_BACKEND_RENDER_TARGET_INCLUDE_HPP
#define HAF_BACKEND_RENDER_TARGET_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>
#include <haf/scene/include/vertex.hpp>
#include <haf/scene/include/vertexarray.hpp>
#include "irenderdata.hpp"
#include "itexture.hpp"
#include "ishader.hpp"
#include "iresourceinfo.hpp"

namespace haf::backend
{
class IRenderTarget : public IResourceInfo
{
public:
    ~IRenderTarget() override {}

    virtual void render(const IRenderData *render_data_begin, const IRenderData *render_data_end) = 0;

    virtual void setViewPort(const mtps::Rectf32 &nviewport) = 0;
    virtual mtps::Rectf32 viewPort() const = 0;
    virtual void setViewRect(const mtps::Rectf32 &nviewRect) = 0;
    virtual mtps::Rectf32 viewRect() const = 0;

    virtual void clear() = 0;
};
} // namespace haf::backend

#endif
