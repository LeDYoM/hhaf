#include "render_data.hpp"

#include "vertex_array_object_private.hpp"
#include <hogl/include/types.hpp>
#include <hogl/include/buffer_functions.hpp>
#include <hogl/include/vao_functions.hpp>
#include <hogl/include/shader_functions.hpp>
#include <hlog/include/hlog.hpp>
#include "default_shader_data.hpp"
#include <glad/glad.h>

using namespace haf::core;

namespace haf::render
{
void RenderData::render()
{
    ogl::bindVAO(vao);
    glBindTextureUnit(0, textureId);
    ogl::useProgram(shader);
    glDrawArrays(GL_TRIANGLES, 0, sizeCount);
    ogl::bindVAO(ogl::invalidHandle());
}

}  // namespace haf::res
