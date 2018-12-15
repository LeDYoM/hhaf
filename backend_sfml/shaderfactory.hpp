#pragma once

#ifndef LIB_BACKEND_SFML_SHADERFACTORY_HPP
#define LIB_BACKEND_SFML_SHADERFACTORY_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <lib/include/backend/iresourcefactories.hpp>
#include "shader.hpp"

namespace lib::backend::sfmlb
{
	class ShaderFactory : public IShaderFactory
	{
	public:
		virtual IShader* loadFromFile(const str &file) override;
        ~ShaderFactory() override;
	private:
        vector<uptr<Shader>> m_shaderCache;
	};
}

#endif
