#include "resource_manager.hpp"
#include "resource_manager_private.hpp"
#include <haf/include/system/subsystem_view.hpp>
#include <hlog/include/hlog.hpp>

#include <haf/include/resources/ittfont.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>
#include <haf/include/resources/ibmp_font.hpp>
#include "default_bmp_font_factory.hpp"

using namespace htps;
using namespace haf::res;

namespace haf::sys
{
ResourceManager::ResourceManager(sys::SystemProvider& system_provider) :
    SystemBase{system_provider},
    p_{muptr<ResourceManagerPrivate>()},
    config_loader_{}
{}

ResourceManager::~ResourceManager() noexcept = default;

void ResourceManager::init()
{
    loadEmbeddedResources();
}

sptr<ITTFont> ResourceManager::getTTFont(const str& rid) const
{
    return get_or_default(p_->ttf_fonts_, rid);
}

sptr<ITexture> ResourceManager::getTexture(const str& rid) const
{
    return get_or_default(p_->textures_, rid);
}

sptr<IShader> ResourceManager::getShader(const str& rid) const
{
    return get_or_default(p_->shaders_, rid);
}

sptr<IFont> ResourceManager::getBMPFont(const str& rid) const
{
    return get_or_default(p_->bmp_fonts_, rid);
}

bool ResourceManager::loadTTFont(const str& rid, const str& fileName)
{
    return get_or_add(this, systemProvider().backendFactory().ttfontFactory(),
                      p_->ttf_fonts_, systemProvider().system<FileSystem>(),
                      rid, fileName) != nullptr;
}
bool ResourceManager::loadTexture(const str& rid, const str& fileName)
{
    return get_or_add(systemProvider().backendFactory().textureFactory(),
                      p_->textures_, systemProvider().system<FileSystem>(), rid,
                      fileName) != nullptr;
}

bool ResourceManager::loadShader(const str& rid, const str& fileName)
{
    return get_or_add(systemProvider().backendFactory().shaderFactory(),
                      p_->shaders_, systemProvider().system<FileSystem>(), rid,
                      fileName) != nullptr;
}

bool ResourceManager::loadBMPFont(const str& rid, const str& fileName)
{
    return get_or_add(this, p_->bmp_font_factory_, p_->bmp_fonts_,
                      systemProvider().system<FileSystem>(), rid,
                      fileName) != nullptr;
}

bool ResourceManager::loadResource(
    res::ResourceDescriptor const& resource_descriptor)
{
    return loadResourceForResource(to_backend(resource_descriptor));
}

str getTextureId()
{
    static int id{0};
    ++id;
    return make_str("ttfont_", id);
}

str ResourceManager::setExternalTexture(backend::ITexture const* texture)
{
    str const id{getTextureId()};
    set_resource(p_->textures_, id, texture);
    return id;
}

bool ResourceManager::loadResourceForResource(
    backend::IResourceDescriptor const& resource_descriptor)
{
    bool result{false};

    if (resource_descriptor.type == kResourceTTFont)
    {
        result =
            loadTTFont(resource_descriptor.name, resource_descriptor.fileName);
    }
    else if (resource_descriptor.type == kResourceTexture)
    {
        result =
            loadTexture(resource_descriptor.name, resource_descriptor.fileName);
    }
    else if (resource_descriptor.type == kResourceBMPFont)
    {
        result =
            loadBMPFont(resource_descriptor.name, resource_descriptor.fileName);
    }
    else if (resource_descriptor.type == kResourceShader)
    {
        result =
            loadShader(resource_descriptor.name, resource_descriptor.fileName);
    }
    else
    {
        LogAsserter::log_assert(result, "Invalid type of element");
    }
    return result;
}

void ResourceManager::setResourcesDirectory(str const& directory)
{
    DisplayLog::debug("Set resources directory to: ", directory);
    config_loader_.setConfigDirectory(directory);
}

SetResourceConfigFileResult ResourceManager::setResourceConfigFile(
    str const& file_name)
{
    return config_loader_.setResourceConfigFile(file_name, subSystemViewer());
}

bool ResourceManager::loadSection(str const& section_name)
{
    return config_loader_.loadSection(section_name, *this);
}

sptr<res::IShader> ResourceManager::getDefaultShader() const
{
    return get_or_default(p_->shaders_, "defaultShader");
}

bool ResourceManager::loadEmbeddedResources()
{
    bool resources_loaded{true};
    resources_loaded &= loadShader("defaultShader", "shader0.txt");

    return resources_loaded;
}

}  // namespace haf::sys
