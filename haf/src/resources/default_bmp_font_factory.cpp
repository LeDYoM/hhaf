#include "default_bmp_font_factory.hpp"
#include "bmp_font.hpp"
#include "texture.hpp"
#include <htypes/include/str.hpp>
#include "resource_loaders/default_resources/default_bmp_font.hpp"
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::res
{
/*
backend::IBMPFont* DefaultBMPFontFactory::loadFromRawMemory(
    RawMemory* raw_memory)
{
    sptr<DefaultBMPFont> font{msptr<DefaultBMPFont>()};
    font->loadFromMemory(raw_memory);
    bmpfont_cache_.push_back(htps::move(font));
    return bmpfont_cache_.back().get();
}
*/
backend::IBMPFont* DefaultBMPFontFactory::loadFromRawMemory(
    backend::ResourceLoadParameters const& resource_load_parameters)
{
    sptr<DefaultBMPFont> font{msptr<DefaultBMPFont>()};
    font->loadFromMemory(resource_load_parameters.raw_memory);

    DisplayLog::debug("Loading font textures");
    const auto& texture_file_names{font->texturesToLoad()};
    DisplayLog::debug("Number of textures to load: ",
                      texture_file_names.size());
    vector<backend::ITexture const*> textures(texture_file_names.size());

    // If no textures in the font, the font is invalid
    if (texture_file_names.empty())
    {
        DisplayLog::error("Invalid font. It has no textures");
        font.reset();
    }

    for (auto&& file_name_and_resource_id : texture_file_names)
    {
        auto const& [file_name, resource_id] = file_name_and_resource_id;
        backend::IResourceDescriptor resource_descriptor{
            resource_id, backend::kResourceTexture,
            "resources/" + /*config_loader_.configDirectory() +*/ file_name};
        bool const texture_available{
            resource_load_parameters.iresource_manager->loadResourceForResource(
                resource_descriptor)};
        if (!texture_available)
        {
            font.reset();
            break;
        }
    }

    bmpfont_cache_.push_back(htps::move(font));
    return bmpfont_cache_.back().get();
}

}  // namespace haf::res
