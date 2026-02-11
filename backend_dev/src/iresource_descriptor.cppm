export module backend_dev:iresource_descriptor;

import htypes;

namespace haf::backend
{
static constexpr char const kResourceTexture[] = "texture";
static constexpr char const kResourceTTFont[]  = "ttf";
static constexpr char const kResourceBMPFont[] = "bmp_font_fnt";
static constexpr char const kResourceShader[]  = "shader";

export struct IResourceDescriptor
{
    htps::str name;
    htps::str type;
    htps::str fileName;
};
}  // namespace haf::backend
