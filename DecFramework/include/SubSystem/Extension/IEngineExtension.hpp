#ifndef DECAYENGINE_IENGINEEXTENSION_HPP
#define DECAYENGINE_IENGINEEXTENSION_HPP

#include "SubSystem/ISubSystem.hpp"

namespace DecFramework::SubSystem::Extension
{
    class IEngineExtension : public ISubSystem
    {
        public:
            ~IEngineExtension() override = default;
    };
}


#endif //DECAYENGINE_IENGINEEXTENSION_HPP
