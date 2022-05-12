HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_IBMPFONT_INTERFACE_INCLUDE_HPP
#define HAF_SCENE_IBMPFONT_INTERFACE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>

#include <haf/include/resources/ifont.hpp>
#include <backend_dev/include/itexture.hpp>

namespace haf::res
{
class IBMPFont : public IFont
{
protected:
    ~IBMPFont() = default;

public:
    virtual htps::vector<htps::str> textureFileNames() const = 0;
    virtual void setTexturePages(
        const htps::vector<backend::ITexture const*>& texture_pages) = 0;
};
}  // namespace haf::res

#endif
