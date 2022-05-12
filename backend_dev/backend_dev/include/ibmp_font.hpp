#ifndef HAF_BACKEND_IBMPFONT_INCLUDE_HPP
#define HAF_BACKEND_IBMPFONT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include "ifont.hpp"
#include "itexture.hpp"

namespace haf::backend
{
class IBMPFont : public IFont
{
protected:
    ~IBMPFont() = default;
public:
    virtual htps::vector<htps::str> textureFileNames() const = 0;
    virtual void setTexturePages(
            const htps::vector<ITexture const*>& texture_pages) = 0;
};
}  // namespace haf::backend

#endif
