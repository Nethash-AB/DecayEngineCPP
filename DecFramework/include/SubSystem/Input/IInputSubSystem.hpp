#ifndef DECAYENGINE_IINPUTSUBSYSTEM_HPP
#define DECAYENGINE_IINPUTSUBSYSTEM_HPP

#include "SubSystem/ISubSystem.hpp"

namespace DecFramework::SubSystem::Input
{
    class IInputSubSystem : public ISubSystem
    {
        public:
            ~IInputSubSystem() override = default;
    };
}

#endif //DECAYENGINE_IINPUTSUBSYSTEM_HPP
