#include "camera.hpp"
#include "conversions.hpp"

namespace haf::backend::sfmlb
{
void Camera::setPointOfView(htps::vector2df const& pov)
{
    view_.setCenter(to_sf_type(pov));
    updateRequired_ = true;
}

void Camera::setViewPort(htps::Rectf32 const& viewPort)
{
    view_.setViewport(to_sf_type(viewPort));
    updateRequired_ = true;
}

void Camera::setNearRect(htps::Rectf32 const& /*nearRect*/)
{

}

void Camera::setFarRect(htps::Rectf32 const& nearRect)
{
    view_.setCenter(to_sf_type(nearRect.center()));
    view_.setSize(to_sf_type(nearRect.size()));
    updateRequired_ = true;
}

bool Camera::updateRequired() const noexcept
{
    return updateRequired_;
}

void Camera::resetUpdateRequired() noexcept
{
    updateRequired_ = false;
}

sf::View const& Camera::getView() noexcept
{
    return view_;
}

}  // namespace haf::backend::sfmlb
