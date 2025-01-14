#ifndef DECAYENGINE_IDECAYOBJECT_HPP
#define DECAYENGINE_IDECAYOBJECT_HPP

#include "EngineSdk.hpp"

namespace DecFramework::Tracking
{
    class IDecayObject
    {
        private:
            std::shared_ptr<IGlobalEnvironment> _gEnv;

            void SetGEnv(const std::shared_ptr<IGlobalEnvironment>& gEnv)
            {
                _gEnv = gEnv;
            }

            template <class>
            friend class DecayObjectTracker;
        protected:
            virtual ~IDecayObject() = default;

            [[nodiscard]] const IGlobalEnvironment* GetGEnv() const
            {
                return _gEnv.get();
            }

            void* operator new(size_t size)
            {
                return ::operator new(size);
            }

            void operator delete(void* block)
            {
                ::operator delete(block);
            }

            void* operator new(size_t size, void* where)
            {
                return ::operator new(size, where);
            }

            void operator delete(void* block, void*)
            {
                ::operator delete(block);
            }
    };
}

#endif //DECAYENGINE_IDECAYOBJECT_HPP
