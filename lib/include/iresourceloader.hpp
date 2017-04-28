#ifndef LIB_IRESOURCELOADER_INCLUDE_HPP
#define LIB_IRESOURCELOADER_INCLUDE_HPP

#pragma once

namespace lib
{
	class IResourceLoader {
	public:
		virtual void loadResources() = 0;
	};
}

#endif
