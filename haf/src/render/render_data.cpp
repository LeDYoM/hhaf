#include <haf/include/render/render_data.hpp>

#include <hogl/include/types.hpp>
#include <hogl/include/buffer_functions.hpp>
#include <hogl/include/vao_functions.hpp>
#include <hogl/include/shader_functions.hpp>
#include <glad/glad.h>

using namespace haf::core;

namespace haf::render
{
void RenderData::render() const
{
    ogl::bindVAO(vao);
    glBindTextureUnit(0, textureId);
    ogl::useProgram(shader);
    glDrawArrays(GL_TRIANGLES, 0, sizeCount);
    ogl::bindVAO(ogl::invalidHandle());
}

}  // namespace haf::res
