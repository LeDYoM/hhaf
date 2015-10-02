#ifndef __LIB_SCENE_HPP__
#define __LIB_SCENE_HPP__

#include "hasname.hpp"

namespace lib
{
	namespace core
	{
		class Scene : public HasName
		{
		public:
			Scene(const std::string &name);
			virtual ~Scene();

			virtual void onActivated() = 0;
			virtual void onDeactivated() = 0;
		};
	}
}

#endif
