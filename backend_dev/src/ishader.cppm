export module backend_dev:ishader;

import :itexture;
import :imaterial_data;
import htypes;
import facil_math;

namespace haf::backend
{
export class IShader
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

