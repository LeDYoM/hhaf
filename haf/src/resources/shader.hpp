HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SHADER_INCLUDE_HPP
#define HAF_SCENE_SHADER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/resources/ishader.hpp>

namespace haf::backend
{
class IShader;
}

namespace haf::res
{
class Shader final : public IShader
{
public:
    Shader(backend::IShader* shader);
    ~Shader();

    void setUniform(htps::str const& name, bool const& value) override;
    void setUniform(htps::str const& name,
                    fmath::vector2df const& value) override;
    void setUniform(htps::str const& name, ITexture* value) override;

    backend::IShader const* backEndShader() const noexcept;

private:
    backend::IShader* priv_;
};
}  // namespace haf::res

#endif
