#ifndef DECAYENGINE_ISUBSYSTEM_HPP
#define DECAYENGINE_ISUBSYSTEM_HPP

#include "EngineSdk.hpp"
#include <cstdint>

FWD_GLOBAL_ENVIRONMENT()

namespace DecFramework::SubSystem
{
    class ISubSystem
    {
        public:
            virtual ~ISubSystem() = default;

            virtual bool IsAlive() = 0;

            virtual void Init(IGlobalEnvironment* gEnv) = 0;
            virtual void Shutdown() = 0;
    };
}

#endif //DECAYENGINE_ISUBSYSTEM_HPP
