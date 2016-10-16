#ifndef LIB_SINGLETON_INCLUDE_HPP
#define LIB_SINGLETON_INCLUDE_HPP

namespace lib
{
	template <class T>
	class Singleton
	{
	protected:
		constexpr Singleton() {}
		virtual ~Singleton() {}
	public:
		inline static T*const createInstance()
		{
			if (!instance_) {
				instance_ = new T{};
			}

			return instance_;
		}

		inline static void destroyInstance()
		{
			if (instance_) {
				delete instance_;
				instance_ = nullptr;
			}
		}

		inline static const T*const getConstInstance() noexcept { return instance_; }
		inline static T* getInstance() noexcept  { return instance_; }

		Singleton(const Singleton&) = delete;
		Singleton&operator=(const Singleton&) = delete;
	private:
		static T* instance_;
	};

	template <class T> T*  Singleton<T>::instance_{ nullptr };
}

#endif
