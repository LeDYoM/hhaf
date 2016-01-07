#ifndef __INCREMENTSCORETOKEN_HPP__
#define __INCREMENTSCORETOKEN_HPP__

#include "lib/types.hpp"
#include "lib/scn/draw/renderizable.hpp"

namespace zoper
{
	class IncrementScoreToken : public lib::scn::draw::Renderizable
	{
	public:
		IncrementScoreToken(const lib::u32 score);
		virtual ~IncrementScoreToken();

		inline bool isActive() const { return _isActive; }
		inline void setActive(bool nv) { _isActive = nv; }
	private:
		bool _isActive;
		lib::u32 _score;
	};
}

#endif
