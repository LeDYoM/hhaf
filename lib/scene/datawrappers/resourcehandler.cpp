#include "resourcehandler.hpp"
#include <lib/resources_interface/include/iresourceloader.hpp>
#include <lib/system/scenemanager.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/include/liblog.hpp>

namespace lib::scene
{
void ResourceHandler::onCreated()
{
    handler_ = &(attachedNode()->sceneManager().resourcesLoader());
    log_assert(handler_ != nullptr, "Invalid IResourceHandler");
}

bool ResourceHandler::loadTTFont(const str &rid, const str &fileName)
{
    return handler_->loadTTFont(rid, fileName);
}

bool ResourceHandler::loadTexture(const str &rid, const str &fileName)
{
    return handler_->loadTexture(rid, fileName);
}

bool ResourceHandler::loadShader(const str &rid, const str &fileName)
{
    return handler_->loadShader(rid, fileName);
}

bool ResourceHandler::loadBMPFont(const str &rid, const str &fileName)
{
    return handler_->loadBMPFont(rid, fileName);
}

void ResourceHandler::loadResources(IResourceLoader& resource_loader)
{
    resource_loader.loadResources(*this);
}

} // namespace lib::scene
