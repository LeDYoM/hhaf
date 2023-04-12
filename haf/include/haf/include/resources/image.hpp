HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_IMAGE_INCLUDE_HPP
#define HAF_RESOURCES_IMAGE_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/resources/iresource.hpp>

namespace haf::res
{
class HAF_API Image final : public IResource
{
public:
    using PixelChannel = core::u8;
    using RGBAPixel    = core::vector4d<PixelChannel>;
    using Coordinate   = core::vector2du32;
    using ImageSize    = core::vector2du32;

    static constexpr ResourceType const StaticResourceType{ResourceType::Image};

    constexpr ResourceType resourceType() const noexcept override
    {
        return StaticResourceType;
    }

    Image() noexcept;
    explicit Image(core::str_view fileName) noexcept;
    Image(Coordinate const& size, const core::u8 channels) noexcept;

    ~Image() override;

    core::u8 pixelSize() const noexcept;
    PixelChannel const* data() const noexcept;

    ImageSize size() const noexcept;
    core::u32 channels() const noexcept;

    bool setPixel(Coordinate const& where, RGBAPixel const& pixel) noexcept;
    RGBAPixel getPixel(Coordinate const& where) const noexcept;
    bool containsImage() const noexcept;
    bool isValid() const noexcept;

    bool validCoordinates(Coordinate const& coordinate) const noexcept;
    bool fill(Coordinate const& start,
              Coordinate const& end,
              RGBAPixel const& pixel) noexcept;

    void fill(RGBAPixel const& pixel) noexcept;

private:
    struct ImagePrivate;
    core::PImplPointer<ImagePrivate> m_p;
};

}  // namespace haf::res

#endif
