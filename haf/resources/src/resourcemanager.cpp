#include "resourcemanager.hpp"
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

#include <backend/include/backendfactory.hpp>

#include <mtypes/include/object.hpp>
#include <mtypes/include/object_utils.hpp>
#include <algorithm>
#include <list>

using namespace mtps;
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
inline auto get_or_default(ResourceList<sptr<T>>& container, const str& rid)
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

    str file_name_;
};

ResourceManager::ResourceManager(sys::SystemProvider& system_provider) :
    SystemBase{system_provider}, p_{muptr<ResourceManagerPrivate>()}
{}

ResourceManager::~ResourceManager() = default;

sptr<ITTFont> ResourceManager::getTTFont(const str& rid)
{
    return get_or_default(p_->ttf_fonts_, rid);
}

sptr<ITexture> ResourceManager::getTexture(const str& rid)
{
    return get_or_default(p_->textures_, rid);
}

sptr<IShader> ResourceManager::getShader(const str& rid)
{
    return get_or_default(p_->shaders_, rid);
}

sptr<IFont> ResourceManager::getBMPFont(const str& rid)
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

bool ResourceManager::setResourceConfigFile(mtps::str file_name)
{
    LogAsserter::log_assert(p_->file_name_.empty(),
                            "The resources file name was already set");

    p_->file_name_ = std::move(file_name);
    return true;
}

bool ResourceManager::loadSection(mtps::str const&)
{
    return true;
}

}  // namespace haf::sys
