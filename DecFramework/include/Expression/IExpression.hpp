#ifndef DECAYENGINE_IEXPRESSION_HPP
#define DECAYENGINE_IEXPRESSION_HPP

#include "Capability/Invocation/IInvocable.hpp"
#include "EngineSdk.hpp"

namespace DecFramework::Expression
{
    template <typename TElement>
    class IExpression : public Capability::Invocation::IConstInvocable<bool, const TElement*>
    {
        public:
            ~IExpression() override = default;

            [[nodiscard]] bool Invoke(const TElement* element) const override = 0;
    };

    template <typename TElement>
    class FunctionExpression : public IExpression<TElement>, public Capability::Invocation::InvocableFunction<bool, const TElement*>
    {
        public:
            FunctionExpression(std::function<bool(TElement)> rhs) : Capability::Invocation::InvocableFunction(std::move(rhs)) {};
            explicit FunctionExpression() = delete;
            ~FunctionExpression() override = default;

            bool Invoke(const TElement* element) const override
            {
                if (!Func) return false;

                return Func(element);
            }
    };
}

#endif //DECAYENGINE_IEXPRESSION_HPP
