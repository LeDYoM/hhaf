#ifndef LOADER_INCLUDE_HPP
#define LOADER_INCLUDE_HPP

#include "loaderexport.hpp"

namespace loader
{
	class LoaderPrivate;
	class Loader
	{
	public:
		Loader();
		~Loader();

		LOADER_API void *loadModule(const char *fileName);
		LOADER_API void *loadMethod(const char *fileName,const char *methodName);
		LOADER_API bool unloadModule(const char *fileName);

	private:
		LoaderPrivate *m_private;
	};

	LOADER_API Loader *createLoader();
	LOADER_API void destroyLoader();
}

#endif
