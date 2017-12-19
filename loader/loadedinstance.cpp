#include "loadedinstance.hpp"
#include <map>
#include <string>

#if defined(_MSC_VER) || defined(__BORLANDC__)
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	inline void *getMethod(void *handle, const char *methodName)
	{
		return static_cast<void*>(GetProcAddress(static_cast<HMODULE>(handle), methodName));
	}

	inline void *loadSharedObject(const char *fileName)
	{
		return static_cast<void*>(LoadLibrary(fileName));
	}

	inline bool freeSharedObject(void *handle)
	{
		return (FreeLibrary(static_cast<HMODULE>(handle)) != 0);
	}
    
    constexpr const char *const extension = ".dll";
#else
    // For now, windows or linux
    #include <dlfcn.h>
	inline void *getMethod(void *handle, const char *methodName)
	{
		return static_cast<void*>(dlsym(handle, methodName));
	}

	inline void *loadSharedObject(const char *fileName)
	{
		return static_cast<void*>(dlopen(fileName, RTLD_NOW));
	}

	inline bool freeSharedObject(void *handle)
	{
		return (dlclose(handle) != 0);
	}   
    constexpr const char *const extension = ".so";
#endif

namespace loader
{
    namespace
    {
        inline bool endsWith (const std::string &fullString, const std::string &ending) {
            return fullString.length() >= ending.length() ? 
                fullString.compare (fullString.length() - ending.length(), ending.length(), ending) == 0 :
                false;
        }
    }

	class LoadedInstancePrivate
	{
	public:
        std::string updateFileExtension(const char *filename) {
            std::string fileName{filename};
            if (!endsWith(fileName, extension)) {
                fileName += extension;
            }
            return fileName;
        }

		void *m_sharedFileHandle{ nullptr };
		std::map<std::string, void*> m_methods;
	};

	LoadedInstance::LoadedInstance() : m_private{ new LoadedInstancePrivate } {}

	LoadedInstance::~LoadedInstance()
	{
		unload();
        delete m_private;
	}

	bool LoadedInstance::load(const char * fileName)
	{
		m_private->m_sharedFileHandle = loadSharedObject(m_private->updateFileExtension(fileName).c_str());
		return loaded();
	}

	void *LoadedInstance::loadMethod(const char *methodName)
	{
		if (loaded()) {
            auto node = m_private->m_methods.find(methodName);
			if (node == m_private->m_methods.end()) {
				auto methodAddress(getMethod(m_private->m_sharedFileHandle, methodName));

				// Add the result of getMethod even if is nullptr to avoid
				// trying to load it more times
				m_private->m_methods[methodName] = methodAddress;
				return methodAddress;
			}
			else {
				// The method is already on the map, return it
				return node->second;
			}
		}
		return nullptr;
	}

	bool LoadedInstance::loaded() const
	{
		return m_private->m_sharedFileHandle != nullptr;
	}

	bool LoadedInstance::unload()
	{
		bool result{ false };

		if (loaded()) {
			result = freeSharedObject(m_private->m_sharedFileHandle);
		}
		m_private->m_sharedFileHandle = nullptr;
		m_private->m_methods.clear();
		return result;
	}

	void *LoadedInstance::loadedData() const
	{
		return m_private->m_sharedFileHandle;
	}

}
