HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_TEXTURE_INCLUDE_HPP
#define HAF_SCENE_TEXTURE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>
#include <haf/include/resources/itexture.hpp>

namespace haf::backend
{
class ITexture;
}

namespace haf::res
{
class Texture final : public ITexture
{
public:
    Texture(backend::ITexture const* texture);
    ~Texture();

    htps::vector2du32 size() const override;

    backend::ITexture const* backEndTexture() const noexcept;

private:
    backend::ITexture const* priv_;
};

}  // namespace haf::res

#endif
