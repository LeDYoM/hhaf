#pragma once

#ifndef LIB_SCENE_SHADER_INCLUDE_HPP__
#define LIB_SCENE_SHADER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/include/backend/ishader.hpp>

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
            bool loadFromFile(const str& filename);
        private:
            struct ShaderPrivate;
            uptr<ShaderPrivate> m_private;
        };
    }
}

#endif
