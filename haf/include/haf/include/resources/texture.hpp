HAF_PRAGMA_ONCE
#ifndef HAF_RESOURCES_TEXTURE_INCLUDE_HPP
#define HAF_RESOURCES_TEXTURE_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/resources/image.hpp>
#include <haf/include/resources/iresource.hpp>

namespace haf::res
{
class HAF_API Texture final : public IResource
{
public:
    static constexpr ResourceType const StaticResourceType{
        ResourceType::Texture};

    constexpr ResourceType resourceType() const noexcept override
    {
        return StaticResourceType;
    }

    Texture();
    Texture(Image const& image);
    ~Texture() override;

    bool isValid() const override;

private:
    struct TexturePrivate;
    core::PImplPointer<TexturePrivate> m_p;
};

}  // namespace haf::res

#endif
