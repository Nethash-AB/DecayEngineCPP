#ifndef DECAYENGINE_IACTIVABLE_HPP
#define DECAYENGINE_IACTIVABLE_HPP

namespace DecFramework::Capability::Activation
{
    class IActivable
    {
        public:
            [[nodiscard]] virtual bool IsActive() const = 0;
            virtual void Activate() = 0;
            virtual void Deactivate() = 0;
        protected:
            virtual ~IActivable() = default;
    };
}

#endif //DECAYENGINE_IACTIVABLE_HPP
