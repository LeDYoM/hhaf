#ifndef HAF_BACKEND_SFMLB_REDNERTARGET_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_REDNERTARGET_INCLUDE_HPP

#include <SFML/Graphics/RenderTarget.hpp>

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

#include <backend_dev/include/irendertarget.hpp>

namespace haf::backend::sfmlb
{
class RenderTarget : public IRenderTarget, public sf::RenderTarget
{
public:
    ~RenderTarget() override;
    void initialize() override;

    void render(const IRenderData* render_data_begin,
                const IRenderData* render_data_end) override;

    void setViewPort(const htps::Rectf32& nviewport) override;
    htps::Rectf32 viewPort() const override;
    void setViewRect(const htps::Rectf32& nviewRect) override;
    htps::Rectf32 viewRect() const override;
    void clear() override;

    htps::str info() const override;
    sf::Vector2u getSize() const override;

};
}  // namespace haf::backend::sfmlb

#endif
