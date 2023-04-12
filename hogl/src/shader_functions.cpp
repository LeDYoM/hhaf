#include <hogl/include/shader_functions.hpp>
#include <htypes/include/array.hpp>
#include <glad/glad.h>

using namespace htps;

namespace haf::ogl
{
namespace
{
Handle createShader(GLenum const shader_type) noexcept
{
    return glCreateShader(shader_type);
}

bool compileShaderImp(Handle const handle, GLchar const* const* code) noexcept
{
    glShaderSource(handle, 1, code, nullptr);
    glCompileShader(handle);
    return true;
}

/*
Handle createAndCompileShader(GLenum const shader_type,
                              str_view const code) noexcept
{
    Handle const shader_handle{createShader(shader_type)};
    auto code_ptr{code.cbegin()};
    compileShaderImp(shader_handle, &code_ptr);
    return shader_handle;
}
*/

}  // namespace

bool compileShader(Handle const handle, str_view const code) noexcept
{
    auto code_ptr{code.cbegin()};
    return compileShaderImp(handle, &code_ptr);
}

Handle createFragmentShader() noexcept
{
    return createShader(GL_FRAGMENT_SHADER);
}

Handle createVertexShader() noexcept
{
    return createShader(GL_VERTEX_SHADER);
}

Handle createProgram() noexcept
{
    return glCreateProgram();
}

void deleteShader(Handle const shader_handle) noexcept
{
    glDeleteShader(shader_handle);
}

void deleteProgram(Handle const program_handle) noexcept
{
    glDeleteProgram(program_handle);
}

void attachShader(Handle const program_handle,
                  Handle const shader_handle) noexcept
{
    glAttachShader(program_handle, shader_handle);
}

void linkProgram(Handle const program_handle) noexcept
{
    glLinkProgram(program_handle);
}

void useProgram(Handle const program_handle) noexcept
{
    glUseProgram(program_handle);
}

void clearUseProgram() noexcept
{
    glUseProgram(invalidHandle());
}

Handle currentProgram() noexcept
{
    GLint result;
    glGetIntegerv(GL_CURRENT_PROGRAM, &result);
    return static_cast<Handle>(result);
}

namespace
{
u32 getNumResourcesOfType(Handle const program, GLenum const type) noexcept
{
    GLint count;
    glGetProgramInterfaceiv(program, type, GL_ACTIVE_RESOURCES, &count);
    return count > 0 ? static_cast<u32>(count) : 0U;
}

bool getResourceData(Handle const program,
                     GLenum const type_request,
                     u32 const index,
                     s32& location,
                     s32& type,
                     s32& array_size,
                     str& name) noexcept
{
    constexpr u32 kNumElements{3U};
    array<GLchar, 256U> nameData{};
    array<GLenum, kNumElements> properties{GL_NAME_LENGTH, GL_TYPE,
                                           GL_ARRAY_SIZE};
    array<GLint, kNumElements> values{};

    glGetProgramResourceiv(program, type_request, index, properties.size(),
                           &properties[0], values.size(), nullptr,
                           values.begin());

    type       = static_cast<s32>(values[1]);
    array_size = static_cast<s32>(values[2]);

    glGetProgramResourceName(program, type_request, index, nameData.size() - 1U,
                             nullptr, nameData.begin());
    name     = nameData.cbegin();
    location = [type_request]() {
        return type_request == GL_PROGRAM_INPUT ? glGetAttribLocation
                                                : glGetUniformLocation;
    }()(program, name.c_str());

    return true;
}

}  // namespace

u32 getNumAttribs(Handle const program) noexcept
{
    return getNumResourcesOfType(program, GL_PROGRAM_INPUT);
}

u32 getNumUniforms(Handle const program) noexcept
{
    return getNumResourcesOfType(program, GL_UNIFORM);
}

bool getAttribData(Handle const program,
                   u32 const attrib_index,
                   s32& location,
                   s32& attrib_type,
                   s32& attrib_array_size,
                   str& name) noexcept
{
    return getResourceData(program, GL_PROGRAM_INPUT, attrib_index, location,
                           attrib_type, attrib_array_size, name);
}

bool getUniformData(Handle const program,
                    u32 const uniform_index,
                    s32& location,
                    s32& uniform_type,
                    s32& uniform_array_size,
                    str& name) noexcept
{
    return getResourceData(program, GL_UNIFORM, uniform_index, location,
                           uniform_type, uniform_array_size, name);
}

void bindAttributeIndex(Handle const program,
                        u32 const index,
                        str_view const name) noexcept
{
    glBindAttribLocation(static_cast<GLuint>(program),
                         static_cast<GLuint>(index),
                         static_cast<GLchar const*>(name.cbegin()));
}

}  // namespace haf::ogl