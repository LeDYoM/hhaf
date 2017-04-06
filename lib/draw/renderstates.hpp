#ifndef LIB_DRAW_RENDERSTATES_HPP
#define LIB_DRAW_RENDERSTATES_HPP

#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/BlendMode.hpp>
#include <SFML/Graphics/Transform.hpp>

#include <lib/draw/transformation.hpp>
#include <lib/draw/texture.hpp>


namespace sf
{
	class Shader;
	class Texture;
}

namespace lib
{
	namespace draw
	{
		class RenderStates
		{
		public:
			RenderStates();
			RenderStates(const Transform &transform, const Texture *texture);
			sf::RenderStates internalStates() const noexcept;
			/*
			RenderStates(const BlendMode& theBlendMode);
			RenderStates(const Transform& theTransform);
			RenderStates(const Texture* theTexture);
			RenderStates(const Shader* theShader);
			RenderStates(const BlendMode& theBlendMode, const Transform& theTransform,
				const Texture* theTexture, const Shader* theShader);
			static const RenderStates Default; ///< Special instance holding the default render states
			*/

//			BlendMode      blendMode; ///< Blending mode
			Transform      m_transform; ///< Transform
			const Texture *m_texture;   ///< Texture
//			const Shader*  shader;    ///< Shader
		};
	}
}

#endif
