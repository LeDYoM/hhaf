#include <lib/resources/include/resourcehandler.hpp>
#include <lib/resources/include/iresourceloader.hpp>
#include <lib/include/liblog.hpp>
#include <lib/system/i_include/get_system.hpp>
#include <lib/resources/i_include/resourcemanager.hpp>

namespace lib::scene
{
void ResourceHandler::onAttached()
{
    log_assert(handler_ == nullptr, "ResourceHandler already attached!");
    handler_ = &(sys::getSystem<sys::ResourceManager>(attachedNode()));
    log_assert(handler_ != nullptr, "Invalid IResourceHandler");
}

bool ResourceHandler::loadTTFont(const mtps::str&rid, const mtps::str&fileName)
{
    return handler_->loadTTFont(rid, fileName);
}

bool ResourceHandler::loadTexture(const mtps::str&rid, const mtps::str&fileName)
{
    return handler_->loadTexture(rid, fileName);
}

bool ResourceHandler::loadShader(const mtps::str&rid, const mtps::str&fileName)
{
    return handler_->loadShader(rid, fileName);
}

bool ResourceHandler::loadBMPFont(const mtps::str&rid, const mtps::str&fileName)
{
    return handler_->loadBMPFont(rid, fileName);
}

void ResourceHandler::loadResources(IResourceLoader& resource_loader)
{
    resource_loader.loadResources(*this);
}

} // namespace lib::scene
