#include "camera.hpp"
#include "conversions.hpp"

namespace haf::backend::sfmlb
{
void Camera::setPointOfView(htps::vector2df const& pov)
{
    view_.setCenter(to_sf_type(pov));
}

void Camera::setViewPort(htps::Rectf32 const& viewPort)
{
    view_.setViewport(to_sf_type(viewPort));
}

void Camera::setNearRect(htps::Rectf32 const& /*nearRect*/)
{

}

void Camera::setFarRect(htps::Rectf32 const& nearRect)
{
    view_.setCenter(to_sf_type(nearRect.center()));
    view_.setSize(to_sf_type(nearRect.size()));
}

}  // namespace haf::backend::sfmlb
