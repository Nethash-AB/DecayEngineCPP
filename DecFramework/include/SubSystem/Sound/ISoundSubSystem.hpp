#ifndef DECAYENGINE_ISOUNDSUBSYSTEM_HPP
#define DECAYENGINE_ISOUNDSUBSYSTEM_HPP

#include "SubSystem/ISubSystem.hpp"

namespace DecFramework::SubSystem::Sound
{
    class ISoundSubSystem : public ISubSystem
    {
        public:
            ~ISoundSubSystem() override = default;
    };
}

#endif //DECAYENGINE_ISOUNDSUBSYSTEM_HPP
