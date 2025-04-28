#include "sfml_shader_factory.hpp"
#include "sfml_shader.hpp"
#include <SFML/Graphics/Shader.hpp>
#include <filesystem>
#include <htypes/include/str_literal.hpp>
#include <iostream>

using namespace htps;

namespace haf::backend::sfmlb
{
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

IShader* SFMLShaderFactory::loadFromRawMemory(
    ResourceLoadParameters const& resource_load_parameters)
{
    static constexpr char kVertexShaderStr[]   = "<vertex_shader>";
    static constexpr char kFragmentShaderStr[] = "<fragment_shader>";
    static constexpr char kGeometryShaderStr[] = "<geometry_shader>";
    static constexpr char kVertexShaderEnd[]   = "</vertex_shader>";
    static constexpr char kFragmentShaderEnd[] = "</fragment_shader>";
    static constexpr char kGeometryShaderEnd[] = "</geometry_shader>";

    str shaders_code{reinterpret_cast<char const*>(
        resource_load_parameters.raw_memory.data())};

    str vertex_shader_code{extractShader(str{kVertexShaderStr},
                                         str{kVertexShaderEnd}, shaders_code)};
    str fragment_shader_code{extractShader(
        str{kFragmentShaderStr}, str{kFragmentShaderEnd}, shaders_code)};
    str geometry_shader_code{extractShader(
        str{kGeometryShaderStr}, str{kGeometryShaderEnd}, shaders_code)};

    std::cout << vertex_shader_code.c_str() << "\n";

    uptr<sf::Shader> shader{muptr<sf::Shader>()};

    bool result{false};
    if (!geometry_shader_code.empty() && !vertex_shader_code.empty() &&
        !fragment_shader_code.empty())
    {
        // 3 shaders to load
        result = shader->loadFromMemory(vertex_shader_code.c_str(),
                                        geometry_shader_code.c_str(),
                                        fragment_shader_code.c_str());
    }
    else if (geometry_shader_code.empty() && !vertex_shader_code.empty() &&
             !fragment_shader_code.empty())
    {
        // vertex and fragment
        result = shader->loadFromMemory(vertex_shader_code.c_str(),
                                        fragment_shader_code.c_str());
    }
    else if (!vertex_shader_code.empty())
    {
        result = shader->loadFromMemory(vertex_shader_code.c_str(),
                                        sf::Shader::Type::Vertex);
    }
    else if (!fragment_shader_code.empty())
    {
        result = shader->loadFromMemory(fragment_shader_code.c_str(),
                                        sf::Shader::Type::Fragment);
    }
    else if (!geometry_shader_code.empty())
    {
        result = shader->loadFromMemory(fragment_shader_code.c_str(),
                                        sf::Shader::Type::Geometry);
    }

    if (result)
    {
        uptr<SFMLShader> t{muptr<SFMLShader>(htps::move(shader))};
        shader_cache_.emplace_back(htps::move(t));
        return (*(shader_cache_.end() - 1)).get();
    }
    return nullptr;
}

SFMLShaderFactory::~SFMLShaderFactory() = default;
}  // namespace haf::backend::sfmlb
