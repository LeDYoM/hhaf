#pragma once

#ifndef HAF_SCENE_TEXTURE_INCLUDE_HPP
#define HAF_SCENE_TEXTURE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <haf/resources/include/itexture.hpp>

namespace haf::backend
{
class ITexture;
}

namespace haf::res
{
class Texture final : public ITexture
{
public:
    Texture(backend::ITexture* texture);
    ~Texture() override;

    mtps::vector2du32 size() const override;

    const backend::ITexture *const backEndTexture() const noexcept;

private:
    backend::ITexture* m_texturePrivate;
};

}  // namespace haf::res

#endif
