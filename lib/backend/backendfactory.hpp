#ifndef LIB_BACKEND_FACTORY_HPP
#define LIB_BACKEND_FACTORY_HPP

#include "iwindow.hpp"
#include "itexturefactory.hpp"

namespace lib
{
	namespace backend
	{
		class BackendFactory final
		{
		public:
			static bool initilialize();
			static bool destroy();
			sptr<IWindowProviderInfo> getWindowProviderInfo();
			sptr<IWindow> getOrCreateWindow();
			sptr<ITextureFactory> getTextureFactory();
			static inline BackendFactory *const instance() noexcept { return m_instance; }
		private:
			BackendFactory();
			~BackendFactory();
			sptr<IWindowProviderInfo> m_windowProviderInfo;
			sptr<IWindow> m_window;
			sptr<ITextureFactory> m_textureFactory;
			static BackendFactory *m_instance;
		};

		static inline BackendFactory &backendFactory() { return *(BackendFactory::instance()); }
		static inline ITextureFactory &textureFactory() { return *(BackendFactory::instance()->getTextureFactory()); }
	}
}
#endif

