#pragma once

#ifndef LIB_SCENE_SHADER_INCLUDE_HPP
#define LIB_SCENE_SHADER_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace lib
{
    namespace backend
    {
        class IShader;
    }

    namespace scene
    {
        class Shader final
        {
        public:
            Shader(backend::IShader *shader);
            ~Shader();
        private:
            struct ShaderPrivate;
            uptr<ShaderPrivate> m_private;
        };
    }
}

#endif
