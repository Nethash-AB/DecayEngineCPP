#ifndef DECAYENGINE_DELEGATE_HPP
#define DECAYENGINE_DELEGATE_HPP

#include "Capability/Equality/IEquatable.hpp"
#include <atomic>
#include <functional>
#include <future>

namespace DecFramework
{
    template <typename Ret, typename... Args>
    class Delegate : public Capability::Equality::IEquatable<Delegate<Ret, Args...>>
    {
        public:
            explicit Delegate(const std::function<Ret(Args...)>& function) : _id(NextId++), _function(function)
            {
            }

            ~Delegate() override = default;

            Ret Invoke(Args... params) const
            {
                if constexpr (std::is_void_v<Ret>)
                {
                    if (_function)
                    {
                        _function(std::forward<Args>(params)...);
                    }
                }
                else
                {
                    if (_function)
                    {
                        return _function(std::forward<Args>(params)...);
                    }
                    return NULL;
                }
            }

            Ret operator()(Args... params) const
            {
                if constexpr (std::is_void_v<Ret>)
                {
                    Invoke(params...);
                }
                else
                {
                    return Invoke(params...);
                }
            }

            [[nodiscard]] bool Equals(const Delegate<Ret, Args...>* other) const override
            {
                return _id == other->_id;
            }
        private:
            static std::atomic<unsigned int> NextId;

            unsigned int _id;
            std::function<Ret(Args...)> _function;
    };

    template <typename Ret, typename... Args>
    std::atomic<unsigned int> Delegate<Ret, Args...>::NextId(0);

    template<typename... Args>
    using Action = Delegate<void, Args...>;
}

#endif //DECAYENGINE_DELEGATE_HPP
