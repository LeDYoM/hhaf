#pragma once

#ifndef LIB_BACKEND_SFML_SHADERFACTORY_HPP
#define LIB_BACKEND_SFML_SHADERFACTORY_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <backend_dev/include/iresourcefactories.hpp>
#include "shader.hpp"

namespace haf::backend::sfmlb
{
    class ShaderFactory : public IShaderFactory
    {
    public:
        virtual IShader* loadFromFile(const mtps::str &file) override;
        ~ShaderFactory() override;
    private:
        mtps::vector<mtps::sptr<Shader>> m_shaderCache;
    };
}

#endif
