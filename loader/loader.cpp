#include "include/loader.hpp"
#include "loadedinstance.hpp"
#include <map>

namespace loader
{
	class LoaderPrivate
	{
	public:
		LoaderPrivate() {}
		~LoaderPrivate() {}
		std::map<std::string, std::shared_ptr<LoadedInstance>> m_loadedInstances;
	};

	static Loader *loaderInstance{ nullptr };

	Loader::Loader()
	{
		m_private = new LoaderPrivate;
	}

	Loader::~Loader()
	{
		if (m_private)
		{
			m_private->m_loadedInstances.clear();
			delete m_private;
			m_private = nullptr;
		}
	}

	void *Loader::loadModule(const char *fileName)
	{
		auto loadedInstace = std::shared_ptr<LoadedInstance>(new LoadedInstance());
		loadedInstace->load(fileName);

		if (loadedInstace->loaded()) {
			m_private->m_loadedInstances[fileName] = loadedInstace;
		}
		return loadedInstace->loadedData();
	}

	void * Loader::loadMethod(const char *fileName, const char *methodName)
	{
		auto iterator(m_private->m_loadedInstances.find(fileName));
		if (iterator != m_private->m_loadedInstances.end()) {
			auto loadedInstance((*iterator).second);
			return loadedInstance->loadMethod(methodName);
		}
		return nullptr;
	}

	bool Loader::unloadModule(const char *fileName)
	{
		auto iterator(m_private->m_loadedInstances.find(fileName));
		if (iterator != m_private->m_loadedInstances.end()) {
			m_private->m_loadedInstances.erase(iterator);
			return true;
		}
		return false;
	}

	Loader * loader::createLoader()
	{
		if (!loaderInstance)
			loaderInstance = new Loader;

		return loaderInstance;
	}

	void destroyLoader()
	{
		if (loaderInstance)
		{
			delete loaderInstance;
			loaderInstance = nullptr;
		}
	}
}
