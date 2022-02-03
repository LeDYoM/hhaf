#include "shaderfactory.hpp"
#include "shader.hpp"
#include <SFML/Graphics/Shader.hpp>
#include "texture.hpp"
#include <filesystem>

using namespace htps;

namespace haf::backend::sfmlb
{
namespace
{
str check_file_exists(const str& base_file, const str& extension)
{
    const str shader_component_file = base_file + extension;
    return std::filesystem::exists(
               std::filesystem::path(shader_component_file.c_str()))
        ? shader_component_file
        : "";
}

str check_vertex_shader_file(const str& base_file)
{
    return check_file_exists(base_file, ".vert");
}

str check_fragment_shader_file(const str& base_file)
{
    return check_file_exists(base_file, ".frag");
}

}  // namespace

IShader* ShaderFactory::loadFromFile(const str& file)
{
    if (::sf::Shader::isAvailable())
    {
        uptr<sf::Shader> shader;
        str const vertex_file{check_vertex_shader_file(file)};
        str const fragment_file{check_fragment_shader_file(file)};

        bool result{false};

        if (!vertex_file.empty() || !fragment_file.empty())
        {
            shader = muptr<sf::Shader>();

            if (fragment_file.empty())
            {
                result = shader->loadFromFile(vertex_file.c_str(),
                                              sf::Shader::Type::Vertex);
            }
            else if (vertex_file.empty())
            {
                result = shader->loadFromFile(vertex_file.c_str(),
                                              sf::Shader::Type::Fragment);
            }
            else
            {
                result = shader->loadFromFile(vertex_file.c_str(),
                                              fragment_file.c_str());
            }

            if (result)
            {
                uptr<Shader> t{muptr<Shader>(std::move(shader))};
                shader_cache_.emplace_back(std::move(t));
                return (*(shader_cache_.end() - 1)).get();
            }
        }
    }
    return nullptr;
}

IShader* ShaderFactory::loadFromRawMemory(htps::RawMemory* raw_memory)
{
    str shaders_code{reinterpret_cast<char const *>(raw_memory->data())};
//    auto const vertex_shader_start{shaders_code.find()}
    return nullptr;
}

ShaderFactory::~ShaderFactory() = default;
}  // namespace haf::backend::sfmlb
