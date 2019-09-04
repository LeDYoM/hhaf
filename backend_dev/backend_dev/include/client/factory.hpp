#pragma once

#ifndef LIB_BACKEND_FACTORY_INCLUDE_HPP
#define LIB_BACKEND_FACTORY_INCLUDE_HPP

namespace lib::backend
{
    template <typename T>
    class IFactoryOf
    {
    public:
        using Interface = T;

        virtual T *const create() noexcept = 0;
        virtual bool destroy(T *) noexcept = 0;
        virtual ~IFactoryOf() {}
    };

    template <typename T, typename ConcreteObject>
    class DefaultFactoryOf : public IFactoryOf<T>
    {
    public:
        T *const create() noexcept override
        {
            return new ConcreteObject;
        }

        bool destroy(T *obj) noexcept override
        {
            delete obj;
            return true;
        }

        ~DefaultFactoryOf() override {}
    };
}

#endif
