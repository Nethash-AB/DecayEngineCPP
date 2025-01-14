#ifndef DECAYENGINE_IPHYSICSSUBSYSTEM_HPP
#define DECAYENGINE_IPHYSICSSUBSYSTEM_HPP

#include "SubSystem/ISubSystem.hpp"

namespace DecFramework::SubSystem::Physics
{
    class IPhysicsSubSystem : public ISubSystem
    {
        public:
            ~IPhysicsSubSystem() override = default;
    };
}

#endif //DECAYENGINE_IPHYSICSSUBSYSTEM_HPP
