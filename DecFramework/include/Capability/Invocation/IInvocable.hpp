#ifndef DECAYENGINE_IINVOCABLE_HPP
#define DECAYENGINE_IINVOCABLE_HPP

#include "Capability/Conversion/IConvertible.hpp"
#include <functional>
#include <type_traits>

namespace DecFramework::Capability::Invocation
{
    namespace
    {
        template<bool IsConst, typename TRet, typename... TArgs>
        class IInvocableImpl;

        template<typename TRet, typename... TArgs>
        class IInvocableImpl<true, TRet, TArgs...> : public Capability::Conversion::IConvertibleTo<std::function<TRet(TArgs...)>>
        {
            public:
                virtual TRet Invoke(TArgs... args) const = 0;

                [[nodiscard]] TRet operator()(TArgs... args) const
                {
                    return Invoke(args...);
                }

                std::function<TRet(TArgs...)> ConvertTo() const override
                {
                    return std::function<TRet(TArgs...)>([this](TArgs... args){
                        return this->Invoke(args...);
                    });
                }
            protected:
                virtual ~IInvocableImpl() = default;
        };

        template<typename... TArgs>
        class IInvocableImpl<true, void, TArgs...> : public Capability::Conversion::IConvertibleTo<std::function<void(TArgs...)>>
        {
            public:
                virtual void Invoke(TArgs... args) const = 0;

                void operator()(TArgs... args) const
                {
                    return Invoke(args...);
                }

                std::function<void(TArgs...)> ConvertTo() const override
                {
                    return std::function<TRet(TArgs...)>([this](TArgs... args){
                        this->Invoke(args...);
                    });
                }
            protected:
                virtual ~IInvocableImpl() = default;
        };

        template<typename TRet, typename... TArgs>
        class IInvocableImpl<false, TRet, TArgs...> : public Capability::Conversion::IConvertibleTo<std::function<TRet(TArgs...)>>
        {
            public:
                virtual TRet Invoke(TArgs... args) = 0;

                [[nodiscard]] TRet operator()(TArgs... args)
                {
                    return Invoke(args...);
                }

                std::function<TRet(TArgs...)> ConvertTo() const override
                {
                    return std::function<TRet(TArgs...)>([this](TArgs... args){
                        return this->Invoke(args...);
                    });
                }
            protected:
                virtual ~IInvocableImpl() = default;
        };

        template<typename... TArgs>
        class IInvocableImpl<false, void, TArgs...> : public Capability::Conversion::IConvertibleTo<std::function<void(TArgs...)>>
        {
            public:
                virtual void Invoke(TArgs... args) = 0;

                void operator()(TArgs... args)
                {
                    return Invoke(args...);
                }

                std::function<void(TArgs...)> ConvertTo() const override
                {
                    return std::function<TRet(TArgs...)>([this](TArgs... args){
                        this->Invoke(args...);
                    });
                }
            protected:
                virtual ~IInvocableImpl() = default;
        };
    }

    template <typename TRet, typename... TArgs>
    using IInvocable = IInvocableImpl<false, TRet, TArgs...>;

    template <typename TRet, typename... TArgs>
    using IConstInvocable = IInvocableImpl<true, TRet, TArgs...>;

    template<typename TRet, typename... TArgs>
    class InvocableFunction : public IInvocable<TRet, TArgs...>, public Capability::Conversion::IConvertibleFrom<std::function<TRet(TArgs...)>>
    {
        public:
            InvocableFunction(const std::function<TRet(TArgs...)>& rhs) : IConvertibleFrom(rhs) {};
            explicit InvocableFunction() = delete;
            ~InvocableFunction() override = default;

            TRet Invoke(TArgs... args) override
            {
                if constexpr (!std::is_void_v<TRet>)
                {
                    if (!Func)
                    {
                        if constexpr (std::is_pointer<TRet>)
                        {
                            return nullptr;
                        }
                        else
                        {
                            return T{};
                        }
                    }
                    else
                    {
                        return Func(args...);
                    }
                }
                else
                {
                    if (Func)
                    {
                        Func(args...);
                    }
                }
            }

            void ConvertFrom(const std::function<TRet(TArgs...)>& rhs) const override
            {
                Func = rhs;
            }
        protected:
            std::function<TRet(TArgs...)> Func;
    };
}

#endif //DECAYENGINE_IINVOCABLE_HPP
