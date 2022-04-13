#ifndef HAF_SCENE_ISHADER_INTERFACE_INCLUDE_HPP
#define HAF_SCENE_ISHADER_INTERFACE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>
#include <htypes/include/str.hpp>
#include <haf/include/resources/itexture.hpp>

namespace haf::res
{
class IShader
{
protected:
    ~IShader() = default;

public:
    virtual void setUniform(htps::str const& name, bool const& value) = 0;
    virtual void setUniform(htps::str const& name,
                            htps::vector2df const& value)             = 0;
    virtual void setUniform(htps::str const& name, ITexture* value)   = 0;
};
}  // namespace haf::res

#endif
