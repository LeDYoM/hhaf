#include <resources/i_include/resourcemanager.hpp>
#include <system/i_include/systemprovider.hpp>
#include <filesystem/i_include/filesystem.hpp>

#include <hlog/include/hlog.hpp>

#include <haf/resources/include/ittfont.hpp>
#include <haf/resources/include/itexture.hpp>
#include <haf/resources/include/ishader.hpp>
#include <resources/i_include/texture.hpp>
#include <resources/i_include/shader.hpp>
#include <resources/i_include/ttfont.hpp>
#include <resources/i_include/bmpfont.hpp>
#include <resources/i_include/bmpfontfactory.hpp>
#include <system/i_include/systemdatawrappercreator.hpp>
#include <haf/filesystem/include/fileserializer.hpp>
#include <backend/include/backendfactory.hpp>

#include <htypes/include/object.hpp>
#include <htypes/include/object_utils.hpp>
#include <algorithm>
#include <list>

using namespace htps;
using namespace haf::res;

namespace haf::sys
{
template <typename T>
using NamedIndex = pair<const str, T>;

template <typename T>
using ResourceList = std::list<NamedIndex<T>>;

namespace
{
template <bool UseInternalFileSystem, typename T, typename V>
inline sptr<T> loadResource(backend::IResourceFactory<V>& factory,
                            FileSystem& fileSystem,
                            const str& fileName)
{
    if constexpr (UseInternalFileSystem)
    {
        RawMemory data(fileSystem.loadBinaryFile(fileName));

        // Prototype / check
        return msptr<T>(factory.loadFromRawMemory(&data));
    }
    else
    {
        return msptr<T>(factory.loadFromFile(fileName));
    }
}

template <typename T>
inline auto get_or_default(ResourceList<sptr<T>> const& container,
                           const str& rid)
{
    auto iterator(
        std::find_if(container.begin(), container.end(),
                     [rid](const auto& node) { return node.first == rid; }));

    return (iterator != container.end()) ? (*iterator).second
                                         : sptr<T>(nullptr);
}

template <bool UseInternalFileSystem, typename V, typename T>
inline sptr<T> get_or_add(backend::IResourceFactory<V>& factory,
                          ResourceList<sptr<T>>& container,
                          FileSystem& fileSystem,
                          const str& rid,
                          const str& fileName)
{
    auto internal_resource(get_or_default(container, rid));

    if (internal_resource != nullptr)
    {
        DisplayLog::info(rid, " found on resource list. Returning instance.");
        return internal_resource;
    }
    else
    {
        // Not found, try to load it.
        DisplayLog::info(rid, " not found on resource list.");
        DisplayLog::info("Going to load file: ", fileName);
        sptr<T> resource(loadResource<UseInternalFileSystem, T>(
            factory, fileSystem, fileName));
        container.emplace_back(rid, resource);
        return resource;
    }
}
}  // namespace

struct ResourceManager::ResourceManagerPrivate
{
    ResourceList<sptr<TTFont>> ttf_fonts_;
    ResourceList<sptr<Texture>> textures_;
    ResourceList<sptr<Shader>> shaders_;
    ResourceList<sptr<BMPFont>> bmp_fonts_;

    BMPFontFactory bmp_font_factory_;
};

ResourceManager::ResourceManager(sys::SystemProvider& system_provider) :
    SystemBase{system_provider},
    p_{muptr<ResourceManagerPrivate>()},
    resources_config_file_name_{}
{}

ResourceManager::~ResourceManager() noexcept = default;

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
    return get_or_add<true>(systemProvider().backendFactory().ttfontFactory(),
                            p_->ttf_fonts_, systemProvider().fileSystem(), rid,
                            fileName) != nullptr;
}
bool ResourceManager::loadTexture(const str& rid, const str& fileName)
{
    return get_or_add<true>(systemProvider().backendFactory().textureFactory(),
                            p_->textures_, systemProvider().fileSystem(), rid,
                            fileName) != nullptr;
}

bool ResourceManager::loadShader(const str& rid, const str& fileName)
{
    return get_or_add<false>(systemProvider().backendFactory().shaderFactory(),
                             p_->shaders_, systemProvider().fileSystem(), rid,
                             fileName) != nullptr;
}

bool ResourceManager::loadBMPFont(const str& rid, const str& fileName)
{
    sptr<BMPFont> bmp_font{p_->bmp_font_factory_.loadFromFile(fileName)};

    if (bmp_font)
    {
        const auto& texture_file_names{bmp_font->textureFileNames()};
        vector<sptr<ITexture>> textures(texture_file_names.size());

        for (const auto& file_name : texture_file_names)
        {
            const bool texture_available =
                loadTexture(rid + "_" + file_name, file_name);

            sptr<ITexture> texture(getTexture(rid + "_" + file_name));
            textures.push_back(std::move(texture));
        }

        bmp_font->setTexturePages(textures);
        p_->bmp_fonts_.emplace_back(rid, bmp_font);
    }
    return bmp_font != nullptr;
}

SetResourceConfigFileResult ResourceManager::parseResourceConfigFile()
{
    LogAsserter::log_assert(!resources_config_file_name_.empty(),
                            "The resources file name was not set");

    SystemDataWrapperCreator dwc{*this};
    auto file_serializer = dwc.dataWrapper<FileSerializer>();
    auto const result    = file_serializer->deserializeFromFileTemplate(
        resources_config_file_name_, resources_config_data_);

    if (result != FileSerializer::Result::Success)
    {
        if (result == FileSerializer::Result::FileIOError)
        {
            DisplayLog::debug("Simulation file ", resources_config_file_name_,
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

SetResourceConfigFileResult ResourceManager::setResourceConfigFile(
    htps::str file_name)
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

bool ResourceManager::loadSection(htps::str const& section_name)
{
    bool global_result{true};

    LogAsserter::log_assert(!resources_config_file_name_.empty(),
                            "The resources file name was not set");

    LogAsserter::log_assert(!resources_config_data_.elements_.empty(),
                            "No data to load");

    // Fetch the section data.
    Object resources_to_load =
        resources_config_data_.elements_[section_name].getObject();

    // Load the section.
    for (auto const& obj : resources_to_load.objects())
    {
        auto const& element_name = obj.first;
        auto const& element_type = obj.second[TypeStr].getValue();
        auto const& element_file = obj.second[FileStr].getValue();
        DisplayLog::debug("Going to load element: ", element_name, " of type ",
                          element_type, " with file name: ", element_file);

        bool local_result{false};

        if (element_type == "ttf")
        {
            local_result = loadTTFont(element_name, element_file);
        }
        else if (element_type == "texture")
        {
            local_result = loadTexture(element_name, element_file);
        }
        else
        {
            // TODO: Load BMPFont
        }

        if (local_result)
        {
            DisplayLog::info("File ", element_file, " loaded as ",
                             element_name);
        }
        else
        {
            DisplayLog::error("File ", element_file, " cannot be loaded");
        }

        global_result &= local_result;
    }

    return global_result;
}

}  // namespace haf::sys
