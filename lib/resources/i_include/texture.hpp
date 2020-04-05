#pragma once

#ifndef LIB_SCENE_TEXTURE_INCLUDE_HPP
#define LIB_SCENE_TEXTURE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <lib/resources/include/itexture.hpp>

namespace haf
{
namespace backend
{
class ITexture;
}
namespace scene
{
class Texture final : public ITexture
{
public:
    Texture(backend::ITexture *texture);
    ~Texture() override;

    mtps::vector2du32 size() const override;

    const backend::ITexture *backEndTexture() const noexcept { return m_texturePrivate; }

private:
    backend::ITexture *m_texturePrivate;
};
} // namespace scene
} // namespace haf

#endif
