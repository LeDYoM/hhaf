#include "resourcefactory.hpp"
#include <mtypes/include/log.hpp>
#include "file.hpp"

namespace lib
{
	namespace core
	{
		ResourceFactory::~ResourceFactory() = default;

		ResourceFactory::ResourceLoadError ResourceFactory::addResourceToLoad(const str & id, const str & fileName)
		{
			if (m_resourceMap.find(id) != m_resourceMap.end()) {
				FileInput fin(fileName);
				if (fin.exists()) {
					auto data = fin.readBinary();

				}
				return ResourceLoadError::FileNotFound;
			}
			return ResourceLoadError::IdAlreadyExists;
		}

	}
}
