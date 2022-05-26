#include "sfml_2d_camera.hpp"
#include "conversions.hpp"

namespace haf::backend::sfmlb
{
SFML2DCamera::~SFML2DCamera() = default;

void SFML2DCamera::setPointOfView(htps::vector2df const& pov)
{
    view_.setCenter(to_sf_type(pov));
    updateRequired_ = true;
}

void SFML2DCamera::setViewPort(htps::Rectf32 const& viewPort)
{
    view_.setViewport(to_sf_type(viewPort));
    updateRequired_ = true;
}

void SFML2DCamera::setNearRect(htps::Rectf32 const& /*nearRect*/)
{

}

void SFML2DCamera::setFarRect(htps::Rectf32 const& nearRect)
{
    view_.setCenter(to_sf_type(nearRect.center()));
    view_.setSize(to_sf_type(nearRect.size()));
    updateRequired_ = true;
}

bool SFML2DCamera::updateRequired() const noexcept
{
    return updateRequired_;
}

void SFML2DCamera::resetUpdateRequired() noexcept
{
    updateRequired_ = false;
}

sf::View const& SFML2DCamera::getView() noexcept
{
    return view_;
}

}  // namespace haf::backend::sfmlb
