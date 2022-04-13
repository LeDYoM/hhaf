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

    virtual void setUniform(htps::str const& name, bool const&v) = 0;
    virtual void setUniform(htps::str const& name, htps::vector2df const& v) = 0;
    virtual void setUniform(htps::str const& name, ITexture const* texture) = 0;

};
}  // namespace haf::backend

#endif
