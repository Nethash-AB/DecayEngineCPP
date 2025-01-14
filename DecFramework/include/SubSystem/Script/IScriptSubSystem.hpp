#ifndef DECAYENGINE_ISCRIPTSUBSYSTEM_HPP
#define DECAYENGINE_ISCRIPTSUBSYSTEM_HPP

#include "SubSystem/ISubSystem.hpp"

namespace DecFramework::SubSystem::Script
{
    class IScriptSubSystem : public ISubSystem
    {
        public:
            ~IScriptSubSystem() override = default;
    };
}

#endif //DECAYENGINE_ISCRIPTSUBSYSTEM_HPP
