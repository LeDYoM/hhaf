#include "incrementscoretokenfactory.hpp"

namespace zoper
{
	IncrementScoreTokenFactory::IncrementScoreTokenFactory(const std::string &name, lib::scn::draw::RenderGroup *parent = nullptr)
		: lib::scn::draw::RenderGroup( name, parent )
	{
	}


	IncrementScoreTokenFactory::~IncrementScoreTokenFactory()
	{
	}

	lib::sptr<IncrementScoreToken> IncrementScoreTokenFactory::getNext(lib::u32 score)
	{
		for (auto node : _renderNodes)
		{
			auto nodeToken = std::dynamic_pointer_cast<IncrementScoreToken>(node);
			if (nodeToken)
			{
				if (!(nodeToken->isActive()))
				{
					return nodeToken;
				}
			}
		}

		auto ist = std::make_shared<IncrementScoreToken>(score);
		addRenderizable(ist);
		return ist;
	}

}
