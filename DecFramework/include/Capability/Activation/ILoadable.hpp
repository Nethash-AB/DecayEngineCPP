#ifndef DECAYENGINE_ILOADABLE_HPP
#define DECAYENGINE_ILOADABLE_HPP

namespace DecFramework::Capability::Activation
{
    class ILoadable
    {
        public:
            [[nodiscard]] virtual bool IsLoaded() const = 0;
            virtual void Load() = 0;
            virtual void Unload() = 0;
        protected:
            virtual ~ILoadable() = default;
    };
}


#endif //DECAYENGINE_ILOADABLE_HPP
