#include <lib/resources/i_include/resourcemanager.hpp>
#include <lib/system/i_include/systemprovider.hpp>
#include <lib/filesystem/i_include/filesystem.hpp>

#include <lib/include/liblog.hpp>

#include <lib/resources/include/ittfont.hpp>
#include <lib/resources/include/itexture.hpp>
#include <lib/resources/include/ishader.hpp>
#include <lib/resources/i_include/texture.hpp>
#include <lib/resources/i_include/shader.hpp>
#include <lib/resources/i_include/ttfont.hpp>
#include <lib/resources/i_include/bmpfont.hpp>
#include <lib/resources/i_include/bmpfontfactory.hpp>

#include <backend/include/backendfactory.hpp>
#include <algorithm>
#include <list>

namespace lib::sys
{
template <typename T>
using NamedIndex = mtps::pair<const mtps::str, T>;

template <typename T>
using ResourceList = std::list<NamedIndex<T>>;

namespace
{
template <bool UseInternalFileSystem, typename T, typename V>
inline mtps::sptr<T> loadResource(backend::IResourceFactory<V> &factory,
                            FileSystem &fileSystem, const mtps::str&fileName)
{
    if constexpr (UseInternalFileSystem)
    {
        mtps::RawMemory data(fileSystem.loadBinaryFile(fileName));

        // Prototype / check
        return mtps::msptr<T>(factory.loadFromRawMemory(&data));
    }
    else
    {
        return mtps::msptr<T>(factory.loadFromFile(fileName));
    }
}

template <typename T>
inline auto get_or_default(ResourceList<mtps::sptr<T>> &container, const mtps::str&rid)
{
    auto iterator(std::find_if(container.begin(), container.end(),
                               [rid](const auto &node) { return node.first == rid; }));

    return (iterator != container.end()) ? (*iterator).second
                                         : mtps::sptr<T>(nullptr);
}

template <bool UseInternalFileSystem, typename V, typename T>
inline mtps::sptr<T> get_or_add(backend::IResourceFactory<V> &factory,
                          ResourceList<mtps::sptr<T>> &container, FileSystem &fileSystem,
                          const mtps::str&rid, const mtps::str&fileName)
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
        mtps::sptr<T> resource(loadResource<UseInternalFileSystem, T>(factory, fileSystem, fileName));
        container.emplace_back(rid, resource);
        return resource;
    }
}
} // namespace

struct ResourceManager::ResourceManagerPrivate
{
    ResourceList<mtps::sptr<scene::TTFont>> ttf_fonts_;
    ResourceList<mtps::sptr<scene::Texture>> textures_;
    ResourceList<mtps::sptr<scene::Shader>> shaders_;
    ResourceList<mtps::sptr<scene::BMPFont>> bmp_fonts_;

    scene::BMPFontFactory bmp_font_factory_;
};

ResourceManager::ResourceManager(sys::SystemProvider &system_provider)
    : AppService{system_provider},
      m_private{mtps::muptr<ResourceManagerPrivate>()} {}

ResourceManager::~ResourceManager() = default;

mtps::sptr<scene::ITTFont> ResourceManager::getTTFont(const mtps::str&rid)
{
    return get_or_default(m_private->ttf_fonts_, rid);
}

mtps::sptr<scene::ITexture> ResourceManager::getTexture(const mtps::str&rid)
{
    return get_or_default(m_private->textures_, rid);
}

mtps::sptr<scene::IShader> ResourceManager::getShader(const mtps::str&rid)
{
    return get_or_default(m_private->shaders_, rid);
}

mtps::sptr<scene::IFont> ResourceManager::getBMPFont(const mtps::str&rid)
{
    return get_or_default(m_private->bmp_fonts_, rid);
}

bool ResourceManager::loadTTFont(const mtps::str&rid, const mtps::str&fileName)
{
    return get_or_add<true>(
        systemProvider().backendFactory().ttfontFactory(),
        m_private->ttf_fonts_, systemProvider().fileSystem(),
        rid, fileName) != nullptr;
}
bool ResourceManager::loadTexture(const mtps::str&rid, const mtps::str&fileName)
{
    return get_or_add<true>(
        systemProvider().backendFactory().textureFactory(),
        m_private->textures_, systemProvider().fileSystem(),
        rid, fileName) != nullptr;
}

bool ResourceManager::loadShader(const mtps::str&rid, const mtps::str&fileName)
{
    return get_or_add<false>(
        systemProvider().backendFactory().shaderFactory(),
        m_private->shaders_, systemProvider().fileSystem(),
        rid, fileName) != nullptr;
}

bool ResourceManager::loadBMPFont(const mtps::str&rid, const mtps::str&fileName)
{
    mtps::sptr<scene::BMPFont> bmp_font{m_private->bmp_font_factory_.loadFromFile(fileName)};

    if (bmp_font)
    {
        const auto &texture_file_names{bmp_font->textureFileNames()};
        mtps::vector<mtps::sptr<scene::ITexture>> textures(texture_file_names.size());

        for (const auto &file_name : texture_file_names)
        {
            const bool texture_available = loadTexture(rid + "_" + file_name, file_name);

            mtps::sptr<scene::ITexture> texture(getTexture(rid + "_" + file_name));
            textures.push_back(std::move(texture));
        }

        bmp_font->setTexturePages(textures);
        m_private->bmp_fonts_.emplace_back(rid, bmp_font);
    }
    return bmp_font != nullptr;
}
} // namespace lib::sys
