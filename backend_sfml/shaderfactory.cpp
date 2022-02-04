#include "shaderfactory.hpp"
#include "shader.hpp"
#include <SFML/Graphics/Shader.hpp>
#include "texture.hpp"
#include <filesystem>
#include <htypes/include/str_literal.hpp>
#include <iostream>

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

namespace
{
str extractShader(str const& start_token,
                  str const& end_token,
                  str const& shaders_code)
{
    auto const index_start{shaders_code.has(start_token)};
    auto const index_end{shaders_code.has(end_token)};

    if (index_start != str::npos && index_end != str::npos)
    {
        str tmp{&shaders_code[index_start + start_token.size()],
                &shaders_code[index_end - 1U]};
        tmp.append("");
        return tmp;
    }
    return str{};
}
}  // namespace

IShader* ShaderFactory::loadFromRawMemory(htps::RawMemory* raw_memory)
{
    static constexpr char kVertexShaderStr[]   = "<vertex_shader>";
    static constexpr char kFragmentShaderStr[] = "<fragment_shader>";
    static constexpr char kGeometryShaderStr[] = "<geometry_shader>";
    static constexpr char kVertexShaderEnd[]   = "</vertex_shader>";
    static constexpr char kFragmentShaderEnd[] = "</fragment_shader>";
    static constexpr char kGeometryShaderEnd[] = "</geometry_shader>";

    str shaders_code{reinterpret_cast<char const*>(raw_memory->data())};

    str vertex_shader_code{extractShader(str{kVertexShaderStr},
                                         str{kVertexShaderEnd}, shaders_code)};
    str fragment_shader_code{extractShader(
        str{kFragmentShaderStr}, str{kFragmentShaderEnd}, shaders_code)};
    str geometry_shader_code{extractShader(
        str{kGeometryShaderStr}, str{kGeometryShaderEnd}, shaders_code)};

    std::cout << vertex_shader_code.c_str() << "\n";

    uptr<sf::Shader> shader{muptr<sf::Shader>()};
    bool const result{shader->loadFromMemory(vertex_shader_code.c_str(),
                                       geometry_shader_code.c_str(),
                                       fragment_shader_code.c_str())};

    if (result)
    {
        uptr<Shader> t{muptr<Shader>(std::move(shader))};
        shader_cache_.emplace_back(std::move(t));
        return (*(shader_cache_.end() - 1)).get();
    }
    return nullptr;
}

ShaderFactory::~ShaderFactory() = default;
}  // namespace haf::backend::sfmlb
