#include <haf/resources/i_include/resourcemanager.hpp>
#include <haf/system/i_include/systemprovider.hpp>
#include <haf/filesystem/i_include/filesystem.hpp>

#include <haf/include/liblog.hpp>

#include <haf/resources/include/ittfont.hpp>
#include <haf/resources/include/itexture.hpp>
#include <haf/resources/include/ishader.hpp>
#include <haf/resources/i_include/texture.hpp>
#include <haf/resources/i_include/shader.hpp>
#include <haf/resources/i_include/ttfont.hpp>
#include <haf/resources/i_include/bmpfont.hpp>
#include <haf/resources/i_include/bmpfontfactory.hpp>

#include <backend/include/backendfactory.hpp>
#include <algorithm>
#include <list>

using namespace mtps;

namespace haf::sys
{
template <typename T>
using NamedIndex = pair<const str, T>;

template <typename T>
using ResourceList = std::list<NamedIndex<T>>;

namespace
{
template <bool UseInternalFileSystem, typename T, typename V>
inline sptr<T> loadResource(backend::IResourceFactory<V> &factory,
                            FileSystem &fileSystem, const str&fileName)
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
inline auto get_or_default(ResourceList<sptr<T>> &container, const str&rid)
{
    auto iterator(std::find_if(container.begin(), container.end(),
                               [rid](const auto &node) { return node.first == rid; }));

    return (iterator != container.end()) ? (*iterator).second
                                         : sptr<T>(nullptr);
}

template <bool UseInternalFileSystem, typename V, typename T>
inline sptr<T> get_or_add(backend::IResourceFactory<V> &factory,
                          ResourceList<sptr<T>> &container, FileSystem &fileSystem,
                          const str&rid, const str&fileName)
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
        sptr<T> resource(loadResource<UseInternalFileSystem, T>(factory, fileSystem, fileName));
        container.emplace_back(rid, resource);
        return resource;
    }
}
} // namespace

struct ResourceManager::ResourceManagerPrivate
{
    ResourceList<sptr<scene::TTFont>> ttf_fonts_;
    ResourceList<sptr<scene::Texture>> textures_;
    ResourceList<sptr<scene::Shader>> shaders_;
    ResourceList<sptr<scene::BMPFont>> bmp_fonts_;

    scene::BMPFontFactory bmp_font_factory_;
};

ResourceManager::ResourceManager(sys::SystemProvider &system_provider)
    : AppService{system_provider},
      m_private{muptr<ResourceManagerPrivate>()} {}

ResourceManager::~ResourceManager() = default;

sptr<scene::ITTFont> ResourceManager::getTTFont(const str&rid)
{
    return get_or_default(m_private->ttf_fonts_, rid);
}

sptr<scene::ITexture> ResourceManager::getTexture(const str&rid)
{
    return get_or_default(m_private->textures_, rid);
}

sptr<scene::IShader> ResourceManager::getShader(const str&rid)
{
    return get_or_default(m_private->shaders_, rid);
}

sptr<scene::IFont> ResourceManager::getBMPFont(const str&rid)
{
    return get_or_default(m_private->bmp_fonts_, rid);
}

bool ResourceManager::loadTTFont(const str&rid, const str&fileName)
{
    return get_or_add<true>(
        systemProvider().backendFactory().ttfontFactory(),
        m_private->ttf_fonts_, systemProvider().fileSystem(),
        rid, fileName) != nullptr;
}
bool ResourceManager::loadTexture(const str&rid, const str&fileName)
{
    return get_or_add<true>(
        systemProvider().backendFactory().textureFactory(),
        m_private->textures_, systemProvider().fileSystem(),
        rid, fileName) != nullptr;
}

bool ResourceManager::loadShader(const str&rid, const str&fileName)
{
    return get_or_add<false>(
        systemProvider().backendFactory().shaderFactory(),
        m_private->shaders_, systemProvider().fileSystem(),
        rid, fileName) != nullptr;
}

bool ResourceManager::loadBMPFont(const str&rid, const str&fileName)
{
    sptr<scene::BMPFont> bmp_font{m_private->bmp_font_factory_.loadFromFile(fileName)};

    if (bmp_font)
    {
        const auto &texture_file_names{bmp_font->textureFileNames()};
        vector<sptr<scene::ITexture>> textures(texture_file_names.size());

        for (const auto &file_name : texture_file_names)
        {
            const bool texture_available = loadTexture(rid + "_" + file_name, file_name);

            sptr<scene::ITexture> texture(getTexture(rid + "_" + file_name));
            textures.push_back(std::move(texture));
        }

        bmp_font->setTexturePages(textures);
        m_private->bmp_fonts_.emplace_back(rid, bmp_font);
    }
    return bmp_font != nullptr;
}
} // namespace haf::sys
