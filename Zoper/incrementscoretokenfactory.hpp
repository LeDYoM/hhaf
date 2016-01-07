#ifndef __INCREMENTSCORETOKENFACTORY_HPP__
#define __INCREMENTSCORETOKENFACTORY_HPP__

#include "incrementscoretoken.hpp"
#include "lib/types.hpp"
#include "lib/scn/draw/rendergroup.hpp"
#include <vector>

namespace zoper
{
	class IncrementScoreTokenFactory : public lib::scn::draw::RenderGroup
	{
	public:
		IncrementScoreTokenFactory(const std::string &name, lib::scn::draw::RenderGroup *parent = nullptr);
		virtual ~IncrementScoreTokenFactory();
		lib::sptr<IncrementScoreToken> getNext(lib::u32 score);


	};
}

#endif
