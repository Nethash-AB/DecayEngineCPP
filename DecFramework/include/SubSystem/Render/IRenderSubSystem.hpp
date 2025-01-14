#ifndef DECAYENGINE_IRENDERSUBSYSTEM_HPP
#define DECAYENGINE_IRENDERSUBSYSTEM_HPP

#include "SubSystem/ISubSystem.hpp"

namespace DecFramework::SubSystem::Render
{
    class IRenderSubSystem : public ISubSystem
    {
        public:
            ~IRenderSubSystem() override = default;
    };
}

#endif //DECAYENGINE_IRENDERSUBSYSTEM_HPP
