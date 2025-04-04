#ifndef HAF_BACKEND_ISHADER_INTERFACE_INCLUDE_HPP
#define HAF_BACKEND_ISHADER_INTERFACE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <facil_math/include/vector2d.hpp>
#include <facil_math/include/rect.hpp>

#include "itexture.hpp"
#include "imaterial_data.hpp"

namespace haf::backend
{
class IShader
{
public:
    virtual ~IShader() = default;

    virtual void setUniform(htps::str const& name, bool const& v)     = 0;
    virtual void setUniform(htps::str const& name,
                            fmath::vector2df const& v)                = 0;
    virtual void setUniform(htps::str const& name,
                            htps::rptr<ITexture const> const texture) = 0;

    virtual void setTexture(htps::size_type const index,
                            ITexture const* const texture) = 0;

    virtual void bind() const   = 0;
    virtual void unbind() const = 0;
};
}  // namespace haf::backend

#endif
