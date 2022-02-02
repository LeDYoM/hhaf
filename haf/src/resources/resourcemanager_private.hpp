#include "resource_manager.hpp"
#include "system/system_provider.hpp"
#include "filesystem/file_system.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "ttfont.hpp"
#include "bmpfont.hpp"
#include "bmpfontfactory.hpp"

#include <htypes/include/dictionary.hpp>
#include <hlog/include/hlog.hpp>

#include <haf/include/resources/ittfont.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>

#include <backend/include/backendfactory.hpp>

#include <htypes/include/object.hpp>
#include <htypes/include/object_utils.hpp>
#include <algorithm>

using namespace htps;
using namespace haf::res;

namespace haf::sys
{
template <typename T>
using ResourceList = htps::Dictionary<T>;

namespace
{
template <typename T, typename V>
inline sptr<T> loadResource(backend::IResourceFactory<V>& factory,
                            FileSystem& fileSystem,
                            const str& fileName)
{
    RawMemory data{fileSystem.loadBinaryFile(fileName)};

    // Prototype / check
    return msptr<T>(factory.loadFromRawMemory(&data));
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

template <typename V, typename T>
sptr<T> get_or_add(backend::IResourceFactory<V>& factory,
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
        sptr<T> resource(loadResource<T>(factory, fileSystem, fileName));
        container.add(rid, resource);
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

}  // namespace haf::sys
