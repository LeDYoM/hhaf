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

    str config_directory_{};
};

}  // namespace haf::sys
