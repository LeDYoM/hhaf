#ifndef HAF_BACKEND_ISHADER_INTERFACE_INCLUDE_HPP
#define HAF_BACKEND_ISHADER_INTERFACE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>
#include <htypes/include/rect.hpp>

#include "itexture.hpp"

namespace haf::backend
{
class IShader
{
public:
    IShader() {}
    virtual ~IShader() {}

    virtual void setUniform(const mtps::str& name, mtps::vector2df v) = 0;
    virtual void setUniform(const mtps::str& name, ITexture* texture) = 0;
};
}  // namespace haf::backend

#endif
