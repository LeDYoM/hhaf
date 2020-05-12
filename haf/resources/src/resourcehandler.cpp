#include <haf/resources/include/resourcehandler.hpp>
#include <haf/resources/include/iresourceloader.hpp>
#include <hlog/include/hlog.hpp>
#include <system/i_include/get_system.hpp>
#include <resources/i_include/resourcemanager.hpp>

using namespace mtps;

namespace haf::scene
{
void ResourceHandler::onAttached()
{
    LogAsserter::log_assert(handler_ == nullptr, "ResourceHandler already attached!");
    handler_ = &(sys::getSystem<sys::ResourceManager>(attachedNode()));
    LogAsserter::log_assert(handler_ != nullptr, "Invalid IResourceHandler");
}

bool ResourceHandler::loadTTFont(const str&rid, const str&fileName)
{
    return handler_->loadTTFont(rid, fileName);
}

bool ResourceHandler::loadTexture(const str&rid, const str&fileName)
{
    return handler_->loadTexture(rid, fileName);
}

bool ResourceHandler::loadShader(const str&rid, const str&fileName)
{
    return handler_->loadShader(rid, fileName);
}

bool ResourceHandler::loadBMPFont(const str&rid, const str&fileName)
{
    return handler_->loadBMPFont(rid, fileName);
}

void ResourceHandler::loadResources(IResourceLoader& resource_loader)
{
    resource_loader.loadResources(*this);
}

} // namespace haf::scene
