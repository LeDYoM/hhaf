#include "resource.hpp"
#include "log.hpp"

namespace lib
{
	namespace core
	{
		Resource::Resource(Resource && other)
			: HasName((HasName&&)other)
		{
			_resourceData = std::move(other._resourceData);
			_isValid = std::move(other._isValid);
			_resourceType = std::move(other._resourceType);
		}

		Resource::Resource(ResourceType rType, const std::string &file, const std::string &id)
			: HasName{ id }
		{
			__ASSERT(rType != ResourceType::Empty && rType != ResourceType::MaxResourceType, "Invalid resource type");

			if (rType == ResourceType::Font)
			{
				logConstruct("Name: ", name(), " of type Font");

				_resourceData.font = new draw::Font();
				_resourceType = ResourceType::Font;
				_isValid = _resourceData.font->loadFromFile(file);
				__ASSERT(_isValid, "File ", file, " not found");
			}
			else if (rType == ResourceType::Texture)
			{
				logConstruct("Name: ", name(), " of type Texture");

				_resourceData.texture = new draw::Texture();
				_resourceType = ResourceType::Texture;
				_isValid = _resourceData.texture->loadFromFile(file);
				__ASSERT(_isValid, "File ", file, " not found");
			}
		}

		Resource::~Resource()
		{
			switch (_resourceType)
			{
			default:
			case ResourceType::Empty:
				__ASSERT(!_resourceData.font, "Deleting resource with data in invalid state");
				delete _resourceData.font;
				break;
			case ResourceType::Font:
				logDestruct("Name: ", name(), " and type Font");
				delete _resourceData.font;
				break;
			case ResourceType::Texture:
				logDestruct("Name: ", name(), " and type Texture");
				delete _resourceData.texture;
				break;
			}
		}
	}
}
