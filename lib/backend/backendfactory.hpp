#ifndef LIB_BACKEND_FACTORY_HPP
#define LIB_BACKEND_FACTORY_HPP

#include "iwindow.hpp"
#include "itexturefactory.hpp"
#include "ittfontfactory.hpp"

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
			sptr<ITTFontFactory> getTTFontFactory();
			static inline BackendFactory *const instance() noexcept { return m_instance; }
		private:
			BackendFactory();
			~BackendFactory();
			sptr<IWindowProviderInfo> m_windowProviderInfo;
			sptr<IWindow> m_window;
			sptr<ITextureFactory> m_textureFactory;
			sptr<ITTFontFactory> m_ttfontFactory;
			static BackendFactory *m_instance;
		};

		static inline BackendFactory &backendFactory() { return *(BackendFactory::instance()); }
		static inline ITextureFactory &textureFactory() { return *(BackendFactory::instance()->getTextureFactory()); }
		static inline ITTFontFactory &ttfontFactory() { return *(BackendFactory::instance()->getTTFontFactory()); }
	}
}
#endif
