#include "resource_manager.hpp"
#include "resourcemanager_private.hpp"
#include <haf/include/system/subsystem_view.hpp>
#include <hlog/include/hlog.hpp>

#include <haf/include/resources/ittfont.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>
#include "bmpfontfactory.hpp"

using namespace haf::res;
using namespace haf::types;

namespace haf::sys
{
ResourceManager::ResourceManager(sys::SystemProvider& system_provider) :
    SystemBase{system_provider},
    p_{types::muptr<ResourceManagerPrivate>()},
    config_loader_{}
{}

ResourceManager::~ResourceManager() noexcept = default;

types::sptr<ITTFont> ResourceManager::getTTFont(const str& rid) const
{
    return get_or_default(p_->ttf_fonts_, rid);
}

types::sptr<ITexture> ResourceManager::getTexture(const str& rid) const
{
    return get_or_default(p_->textures_, rid);
}

types::sptr<IShader> ResourceManager::getShader(const str& rid) const
{
    return get_or_default(p_->shaders_, rid);
}

types::sptr<IFont> ResourceManager::getBMPFont(const str& rid) const
{
    return get_or_default(p_->bmp_fonts_, rid);
}

bool ResourceManager::loadTTFont(const str& rid, const str& fileName)
{
    return get_or_add(systemProvider().backendFactory().ttfontFactory(),
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
    types::sptr<BMPFont> bmp_font{p_->bmp_font_factory_.loadFromFile(fileName)};
    return loadBmpFontTextures(bmp_font, rid, fileName);
}

bool ResourceManager::loadBmpFontTextures(htps::sptr<res::BMPFont> bmp_font,
                                          const htps::str& rid,
                                          const htps::str& fileName)
{
    if (bmp_font)
    {
        DisplayLog::debug("Font config file ", fileName,
                          " loaded and parsed successfully");
        DisplayLog::debug("Loading font textures");
        const auto& texture_file_names{bmp_font->textureFileNames()};
        DisplayLog::debug("Number of textures to load: ",
                          texture_file_names.size());
        vector<types::sptr<ITexture>> textures(texture_file_names.size());

        // If no textures in the font, the font is invalid
        if (texture_file_names.empty())
        {
            DisplayLog::error("Invalid font. It has no textures");
            bmp_font.reset();
        }

        for (const auto& file_name : texture_file_names)
        {
            const bool texture_available =
                loadTexture(rid + "_" + file_name,
                            config_loader_.configDirectory() + file_name);

            (void)(texture_available);
            DisplayLog::debug_if(!texture_available,
                                 "Texture for font not found: ", file_name);

            types::sptr<ITexture> texture(getTexture(rid + "_" + file_name));
            textures.emplace_back(std::move(texture));
        }

        bmp_font->setTexturePages(textures);
        p_->bmp_fonts_.add(rid, bmp_font);
    }
    else
    {
        DisplayLog::debug("Cannot load bmp font: ", fileName);
    }
    return bmp_font != nullptr;
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

}  // namespace haf::sys
