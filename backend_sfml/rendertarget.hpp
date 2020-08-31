#pragma once

#ifndef HAF_BACKEND_SFMLB_REDNERTARGET_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_REDNERTARGET_INCLUDE_HPP

#include <SFML/Graphics/RenderTarget.hpp>

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include <backend_dev/include/irendertarget.hpp>

namespace haf::backend::sfmlb
{
class RenderTarget : public IRenderTarget, public sf::RenderTarget
{
    void initialize() override;

    void render(const IRenderData* render_data_begin,
                const IRenderData* render_data_end) override;

    void setViewPort(const mtps::Rectf32& nviewport) override;
    mtps::Rectf32 viewPort() const override;
    void setViewRect(const mtps::Rectf32& nviewRect) override;
    mtps::Rectf32 viewRect() const override;
    void clear() override;

    mtps::str info() const override;
    sf::Vector2u getSize() const override;

};
}  // namespace haf::backend::sfmlb

#endif
