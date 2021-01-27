#ifndef HAF_SYSTEM_TESTS_UTILS_INCLUDE_HPP
#define HAF_SYSTEM_TESTS_UTILS_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <system/i_include/systemprovider.hpp>
#include <system/i_include/systemdatawrappercreator.hpp>
#include <haf/system/include/datawrappercreator.hpp>
#include <shareddata/i_include/shareddatasystem.hpp>
#include <time/i_include/timesystem.hpp>
#include <system/i_include/init_system_options.hpp>

class TestSystem
{
public:
    TestSystem() : system_provider_{}, init_system_options_{} {}

    void init()
    {
        setInitSystemOptions(init_system_options_);
        system_provider_.fastInit(init_system_options_);
    }

    virtual ~TestSystem() = default;

    virtual void setInitSystemOptions(haf::sys::InitSystemOptions&) = 0;

    inline haf::sys::SharedDataSystem& sharedDataSystem()
    {
        return system_provider_.sharedDataSystem();
    }

    inline haf::sys::SharedDataSystem const& sharedDataSystem() const
    {
        return system_provider_.sharedDataSystem();
    }

    inline haf::sys::TimeSystem& timeSystem()
    {
        return system_provider_.timeSystem();
    }

    inline haf::sys::TimeSystem const& timeSystem() const
    {
        return system_provider_.timeSystem();
    }

    haf::sys::SystemProvider& systemProvider() noexcept
    {
        return system_provider_;
    }

    haf::sys::SystemProvider const& systemProvider() const noexcept
    {
        return system_provider_;
    }

private:
    haf::sys::SystemProvider system_provider_;
    haf::sys::InitSystemOptions init_system_options_;
};

class TestSharedDataSystem : public TestSystem
{
public:
    haf::sys::SystemDataWrapperCreator get()
    {
        return haf::sys::SystemDataWrapperCreator{
            systemProvider().sharedDataSystem()};
    }

private:
    void setInitSystemOptions(
        haf::sys::InitSystemOptions& init_system_options) override
    {
        init_system_options.init_shared_data_system = true;
    }
};

class TestTimeSystem : public TestSystem
{
public:
    haf::sys::SystemDataWrapperCreator get()
    {
        return haf::sys::SystemDataWrapperCreator{
            systemProvider().timeSystem()};
    }

private:
    void setInitSystemOptions(
        haf::sys::InitSystemOptions& init_system_options) override
    {
        init_system_options.init_time_system = true;
    }
};

template <typename T>
mtps::uptr<T> makeTestSystem()
{
    auto t = mtps::muptr<T>();
    t->init();
    return t;
}

#endif
