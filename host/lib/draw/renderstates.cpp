#include "renderstates.hpp"
#include "transformation.hpp"
#include "texture.hpp"

namespace lib
{
	namespace draw
	{
		RenderStates::RenderStates() = default;
		RenderStates::~RenderStates() = default;

		void RenderStates::newFrame()
		{
			m_renderStates = sf::RenderStates{};
		}
		sf::RenderStates RenderStates::prepareNewElement(const Transform *transform, const sf::Texture * texture)
		{
			return sf::RenderStates(m_renderStates.blendMode, 
				transform ? m_renderStates.transform*(*transform):m_renderStates.transform,
				texture,
				m_renderStates.shader);
		}
		RenderStatesStackHandle RenderStates::pushChanges(const Transform *transform, const sf::Texture * texture)
		{
			m_statesStack.emplace(std::move(m_renderStates));
			m_renderStates = prepareNewElement(transform, texture);
			return RenderStatesStackHandle(*this);
		}
		void RenderStates::popChanges()
		{
			m_renderStates = m_statesStack.top();
			m_statesStack.pop();
		}

		RenderStatesStackHandle::~RenderStatesStackHandle()
		{
			m_stack.popChanges();
		}

		RenderStatesStackHandle::RenderStatesStackHandle(RenderStates & stack)
			: m_stack{ stack } {}
	}
}
