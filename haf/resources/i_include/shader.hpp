#ifndef HAF_SCENE_SHADER_INCLUDE_HPP
#define HAF_SCENE_SHADER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/resources/include/ishader.hpp>

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
    ~Shader() override;

    backend::IShader const* backEndShader() const noexcept;

private:
    backend::IShader* m_ShaderPrivate;
};
}  // namespace haf::res

#endif
