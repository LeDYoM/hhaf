#include "resourcemanager.hpp"
#include "resourcemanager_private.hpp"
#include "system/systemprovider.hpp"

#include <hlog/include/hlog.hpp>

#include <haf/include/resources/ittfont.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>
#include "bmpfontfactory.hpp"
#include "system/systemdatawrappercreator.hpp"

using namespace haf::res;
using namespace haf::types;

namespace haf::sys
{
ResourceManager::ResourceManager(sys::SystemProvider& system_provider) :
    SystemBase{system_provider},
    p_{types::muptr<ResourceManagerPrivate>()},
    resources_config_file_name_{}
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
            const bool texture_available = loadTexture(
                rid + "_" + file_name, p_->config_directory_ + file_name);

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

SetResourceConfigFileResult ResourceManager::parseResourceConfigFile()
{
    LogAsserter::log_assert(!resources_config_file_name_.empty(),
                            "The resources file name was not set");

    SystemDataWrapperCreator dwc{*this};
    auto file_serializer = dwc.dataWrapper<FileSerializer>();
    auto const result    = file_serializer->deserializeFromFile(
        resources_config_file_name_, resources_config_data_);

    if (result != FileSerializer::Result::Success)
    {
        if (result == FileSerializer::Result::FileIOError)
        {
            DisplayLog::debug("Resources file ", resources_config_file_name_,
                              " not found");
            return SetResourceConfigFileResult::FileNotFound;
        }
        else if (result == FileSerializer::Result::ParsingError)
        {
            DisplayLog::error("File ", resources_config_file_name_,
                              " found but contains invalid format.");
            return SetResourceConfigFileResult::ParseError;
        }
        else
        {
            DisplayLog::error(
                "Unknow error reading and parsing simulation file: ",
                resources_config_file_name_);
            return SetResourceConfigFileResult::UnknownError;
        }
    }
    return SetResourceConfigFileResult::Ok;
}

void ResourceManager::setResourcesDirectory(str const& directory)
{
    DisplayLog::debug("Set resources directory to: ", directory);
    p_->config_directory_ = std::move(directory);
}

SetResourceConfigFileResult ResourceManager::setResourceConfigFile(
    str const& file_name)
{
    LogAsserter::log_assert(
        !file_name.empty(),
        "Trying to set an empty file name for resources file");

    if (file_name == resources_config_file_name_)
    {
        // It is ok to set the same resources file again.
        return SetResourceConfigFileResult::AlreadySet;
    }

    LogAsserter::log_assert(resources_config_file_name_.empty(),
                            "The resources file name was already set");

    resources_config_file_name_ = std::move(file_name);
    return parseResourceConfigFile();
}

namespace
{
static constexpr char TypeStr[] = "type";
static constexpr char FileStr[] = "file";
}  // namespace

bool ResourceManager::loadSection(str const& section_name)
{
    bool global_result{true};

    LogAsserter::log_assert(!resources_config_file_name_.empty(),
                            "The resources file name was not set");

    // Fetch the section data.
    auto const resources_to_load_iterator{
        resources_config_data_.elements.cfind_checked(section_name)};

    if (resources_to_load_iterator.first)
    {
        // Load the section.
        for (auto const& resource_to_load :
             resources_to_load_iterator.second->second)
        {
            DisplayLog::debug("Going to load element: ", resource_to_load.name,
                              " of type ", resource_to_load.type,
                              " with file name: ", resource_to_load.file_name);

            str element_file{resource_to_load.file_name};
            if (!p_->config_directory_.empty())
            {
                element_file = p_->config_directory_ + element_file;
                DisplayLog::debug("Element file with directory: ",
                                  element_file);
            }

            bool local_result{false};

            if (resource_to_load.type == "ttf")
            {
                local_result = loadTTFont(resource_to_load.name, element_file);
            }
            else if (resource_to_load.type == "texture")
            {
                local_result = loadTexture(resource_to_load.name, element_file);
            }
            else if (resource_to_load.type.starts_with("bmp_font"))
            {
                local_result = loadBMPFont(resource_to_load.name, element_file);
            }
            else
            {
                LogAsserter::log_assert(local_result,
                                        "Invalid type of element");
            }

            if (local_result)
            {
                DisplayLog::info("File ", element_file, " loaded as ",
                                 resource_to_load.name);
            }
            else
            {
                DisplayLog::error("File ", element_file, " cannot be loaded");
            }

            global_result &= local_result;
        }
    }

    return global_result;
}

}  // namespace haf::sys
