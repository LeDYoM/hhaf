#include "rendertarget.hpp"
#include "conversions.hpp"
#include <backend_dev/include/ivertex.hpp>

#include <SFML/Config.hpp>

using namespace mtps;

namespace haf::backend::sfmlb
{
static_assert(sizeof(sf::Vertex) == sizeof(iVertex),
              "Incomptable version of SFML");

void RenderTarget::render(const IRenderData* render_data_begin,
                          const IRenderData* render_data_end)
{
    while (render_data_begin != render_data_end)
    {
        sf::RenderTarget::draw(
            to_sf_type((*render_data_begin).vertices),
            static_cast<size_type>((*render_data_begin).nVertex),
            to_sf_type((*render_data_begin).pType),
            to_sf_type((*render_data_begin).transform,
                       (*render_data_begin).texture,
                       (*render_data_begin).shader));
        ++render_data_begin;
    }
}

void RenderTarget::setViewPort(const Rectf32& nviewport)
{
    sf::View currentView(getView());
    currentView.setViewport(to_sf_type(nviewport));
    setView(currentView);
}

Rectf32 RenderTarget::viewPort() const
{
    sf::View currentView(getView());
    return from_sft_type(currentView.getViewport());
}

void RenderTarget::setViewRect(const Rectf32& nviewRect)
{
    sf::View currentView(getView());
    currentView.setCenter(to_sf_type(nviewRect.center()));
    currentView.setSize(to_sf_type(nviewRect.size()));
    setView(currentView);
}

Rectf32 RenderTarget::viewRect() const
{
    sf::View currentView(getView());
    return rectFromCenterAndSize(from_sf_type(currentView.getCenter()),
                                 from_sf_type(currentView.getSize()));
}

void RenderTarget::clear()
{
    sf::RenderTarget::clear();
}

mtps::str RenderTarget::info() const
{
    return make_str(
        "name:SFMLWindowRenderTargget;provider:SFML;provider_version:",
        SFML_VERSION_MAJOR, ".", SFML_VERSION_MINOR, ".", SFML_VERSION_PATCH,
        ";version:0;subversion:2:patch3");
}
}  // namespace haf::backend::sfmlb
